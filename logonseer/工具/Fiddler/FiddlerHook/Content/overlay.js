/*
 * Copyright (c)2015 Telerik
 *
 * Permission to use, copy, modify, and distribute this file for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * */
Components.utils.import("resource://gre/modules/Services.jsm");

var fiddlerhook = {
    iInterval: 0,
    iFiddlerPort: 8888,
    isFiddlerListening: false,
    bWatchSSL: true,
    prefsProxy: null,
    prefsHook: null,
    oDynamicKey: null,

    //
    // This function is executed when our addon is loaded
    //
    onLoad: function () {
        this.initialized = true;
        this.strings = document.getElementById("fiddlerhook-strings");

        document.getElementById('status-bar-panel-FiddlerHook').label = "Loading FiddlerHook...";

        // https://developer.mozilla.org/En/NsIPrefBranch2 
        this.prefsHook = Services.prefs.getBranch("extensions.fiddlerhook.");
        this.prefsHook.QueryInterface(Components.interfaces.nsIPrefBranch2);		// Enables observers in FF <13
        this.prefsHook.addObserver("", this, false);

        this.prefsProxy = Services.prefs.getBranch("network.proxy.");
        this.prefsProxy.QueryInterface(Components.interfaces.nsIPrefBranch2);
        this.prefsProxy.addObserver("", this, false);

        // Set up a monitor the Fiddler2\Dynamic\Attached key
        this.hookFiddlersDynamicKey();
        this.iInterval = setInterval(this.queryRegistry, 1000, this);

        // Hide the status bar item if that's what the user wants.
        var bShowSB = this.prefsHook.getBoolPref("showstatusbar", true);
        document.getElementById('miMainShowSB').setAttribute('checked', bShowSB);
        document.getElementById('status-bar-panel-FiddlerHook').setAttribute('hidden', !bShowSB);

        var iHookMode = 0;
        try {
            iHookMode = this.prefsHook.getIntPref("hookmode");
        }
        catch (e) { }
        switch (iHookMode) {
            case 1:
                this.doAttach();
                break;
            case 2:
                this.doAutoUpdate();
                break;
        }
        this.updateFiddlerHookUI();
    },

    //
    // This function is called when our addon is unloaded.  It stops monitoring the keys.
    //
    onUnload: function () {
        window.clearInterval(this.iInterval);

        if (null != this.oDynamicKey) {
            this.oDynamicKey.stopWatching();
            this.oDynamicKey.close();
        }

        if (null != this.prefsHook) {
            this.prefsHook.removeObserver("", this);
        }

        if (null != this.prefsProxy) {
            this.prefsProxy.removeObserver("", this);
        }

        // If there are no more windows, detach so that we don't leave outdated settings around for next boot.
        var wm = Components.classes["@mozilla.org/appshell/window-mediator;1"].getService(Components.interfaces.nsIWindowMediator);
        var enumerator = wm.getEnumerator("navigator:browser");
        if (!enumerator.hasMoreElements()) {
            this.doDetach();
        }
    },

    // 
    // Try to open the Fiddler's registry keys and read its settings.
    // Then, get the isFiddlerListening value and set up an observer for changes.
    //
    hookFiddlersDynamicKey: function () {
        try {
            var wrk = Components.classes["@mozilla.org/windows-registry-key;1"].createInstance(Components.interfaces.nsIWindowsRegKey);
            wrk.open(wrk.ROOT_KEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Fiddler2", wrk.ACCESS_READ); // The required ACCESS_NOTIFY bit is in the ACCESS_READ value
            this.iFiddlerPort = wrk.readIntValue("ListenPort");
            this.bWatchSSL = ("True" == wrk.readStringValue("CaptureCONNECT"));
            this.oDynamicKey = wrk.openChild("Dynamic", wrk.ACCESS_READ);
            this.oDynamicKey.startWatching(false);

            try {
                this.isFiddlerListening = (1 == this.oDynamicKey.readIntValue("Attached"));
            }
            catch (e) { }

            return true;
        }
        catch (e) {
            Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("FiddlerHook Monitoring Error: " + e.message);
            return false;
        }
    },

    //
    // This function updates UI elements to match the current monitoring mode
    //
    updateFiddlerHookUI: function () {
        if (null == document) return;
        // Determine the current hook mode
        var iHookMode = 0;
        try {
            iHookMode = this.prefsHook.getIntPref("hookmode");
        }
        catch (e) { }

        // Update status bar and menu state
        switch (iHookMode) {
            case 0:
                document.getElementById('rdoMainFHOptionDisable').setAttribute('checked', 'true');
                document.getElementById('rdoFHOptionDisable').setAttribute('checked', 'true');
                document.getElementById('status-bar-panel-FiddlerHook').label = "Fiddler: Disabled";
                break;

            case 1:
                document.getElementById('rdoMainFHOptionForce').setAttribute('checked', 'true');
                document.getElementById('rdoFHOptionForce').setAttribute('checked', 'true');
                document.getElementById('status-bar-panel-FiddlerHook').label = "Fiddler: ForceOn";
                break;

            case 2:
                document.getElementById('rdoMainFHOptionOpportune').setAttribute('checked', 'true');
                document.getElementById('rdoFHOptionOpportune').setAttribute('checked', 'true');
                document.getElementById('status-bar-panel-FiddlerHook').label =
                        (this.isFiddlerListening == 1) ? "Fiddler: ON (auto)" : "Fiddler: OFF (auto)";
                break;
        }
    },

    //
    // This callback function executes if the \Software\Microsoft\Fiddler2\Dynamic\Attached DWORD changes
    //
    queryRegistry: function (oObj) {
        if ((null == oObj.oDynamicKey) || !oObj.oDynamicKey.hasChanged()) return;  // Bail quickly

        var i = 0;
        try {
            i = oObj.oDynamicKey.readIntValue("Attached");
        }
        catch (e) {
            i = 0;
        }

        // "this" isn't the object you might expect, so we pass 'ourselves' using oObj.  There's a good (complicated) reason for that; 
        // see https://developer.mozilla.org/en/Core_JavaScript_1.5_Reference/Operators/Special_Operators/this_Operator#Method_binding
        oObj.isFiddlerListening = (1 == i);
        oObj.doAutoUpdate();
        oObj.updateFiddlerHookUI();
    },

    //
    // This callback function executes if any of the preference values we care about have changed.
    //
    observe: function (subject, topic, data) {
        if (topic != "nsPref:changed") {
            return;
        }

        switch (data) {
            // network.proxy.* preferences
            case "type":
            case "http":
            case "http_port":
                // The user may have modified the network.proxy.type preferences using the UI.
                // TODO: If settings are not pointing at us but should be, we should change our UI to "disabled"?
                // 	if (	(this.prefsProxy.getIntPref("type") == 1) && (this.prefsProxy.getCharPref("http") == "127.0.0.1") && (this.prefsProxy.getIntPref("http_port") == 8888))
                break;

            // extension.fiddlerhook.* preferences
            case "hookmode":
                this.updateFiddlerHookUI();
                break;

            case "showstatusbar":
                var bShowSB = this.prefsHook.getBoolPref("showstatusbar", true);
                document.getElementById('status-bar-panel-FiddlerHook').setAttribute('hidden', !bShowSB);
                break;
        }
    },

    //
    // This function executes when the user changes the monitoring option using the status bar menu or tools menu
    //
    onMenuCommand: function (e) {
        //Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("MenuCommand: " + e.target.id);
        switch (e.target.id) {
            case "rdoMainFHOptionOpportune":
            case "rdoFHOptionOpportune":
                this.prefsHook.setIntPref("hookmode", 2);
                this.doAutoUpdate();
                break;

            case "rdoMainFHOptionForce":
            case "rdoFHOptionForce":
                this.prefsHook.setIntPref("hookmode", 1);
                this.doAttach();
                break;

            case "rdoMainFHOptionDisable":
            case "rdoFHOptionDisable":
                this.prefsHook.setIntPref("hookmode", 0);
                this.doDetach();
                break;

            case "miMainShowSB":
                var bShowSB = ("true" === document.getElementById('miMainShowSB').getAttribute('checked'));
                this.prefsHook.setBoolPref("showstatusbar", bShowSB);
                document.getElementById('status-bar-panel-FiddlerHook').setAttribute('hidden', !bShowSB);
            default:
                return; 		// throw exception?
                break;
        }

        this.updateFiddlerHookUI();
    },

    //
    // This function is called to handle Fiddler attach/detach changes
    //
    doAutoUpdate: function () {
        // window.alert(window, "AutoUpdate", "hookmode: " + this.prefsHook.getIntPref("hookmode")+"\n"+ this.isFiddlerListening  );
        if (2 != this.prefsHook.getIntPref("hookmode")) return;

        if (null == this.oDynamicKey) {
            if (!this.hookFiddlersDynamicKey()) { this.isFiddlerListening = false; }
        }

        if (this.isFiddlerListening) {
            this.doAttach();
        }
        else {
            this.doDetach();
        }

        this.updateFiddlerHookUI();
    },

    doAttach: function () {
        if (null == this.prefsProxy) return; 	// Assert?

        if ((this.prefsProxy.getIntPref("type") == 1) &&
            (this.prefsProxy.getCharPref("http") == "127.0.0.1") &&
            (this.prefsProxy.getIntPref("http_port") == this.iFiddlerPort)) {
            Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("FiddlerHook already attached; skipping backups.");
        }
        else {
            // Backup the prior proxy settings so they can be reverted later
            try {
                this.prefsHook.setIntPref("backup-proxytype", this.prefsProxy.getIntPref("type"));
                this.prefsHook.setCharPref("backup-proxysockshost", this.prefsProxy.getCharPref("socks"));
                this.prefsHook.setCharPref("backup-proxyhttphost", this.prefsProxy.getCharPref("http"));
                this.prefsHook.setIntPref("backup-proxyhttpport", this.prefsProxy.getIntPref("http_port"));
                this.prefsHook.setCharPref("backup-proxysslhost", this.prefsProxy.getCharPref("ssl"));
                this.prefsHook.setIntPref("backup-proxysslport", this.prefsProxy.getIntPref("ssl_port"));
                this.prefsHook.setCharPref("backup-no_proxies_on", this.prefsProxy.getCharPref("no_proxies_on"));
            }
            catch (e) {
                Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("FiddlerHook Error when backing up old configuration: " + e.message);
            }
        }

        // Point Firefox at Fiddler here...
        try {
            this.prefsProxy.setIntPref("type", 1);  //http://kb.mozillazine.org/Network.proxy.type
            this.prefsProxy.setCharPref("http", "127.0.0.1");
            this.prefsProxy.setIntPref("http_port", this.iFiddlerPort);

            // Ensure no SOCKS proxy
            this.prefsProxy.setCharPref("socks", "");

            // Only hook SSL if Fiddler is set to capture connects.	
            if (this.bWatchSSL) {
                this.prefsProxy.setCharPref("ssl", "127.0.0.1");
                this.prefsProxy.setIntPref("ssl_port", this.iFiddlerPort);
            }
            else {
                // If we're not supposed to be watching SSL, make sure we're not.
                if ((this.prefsProxy.getCharPref("ssl") == "127.0.0.1") && (this.prefsProxy.getIntPref("ssl_port") == this.iFiddlerPort)) {
                    this.prefsProxy.setCharPref("ssl", "");
                    this.prefsProxy.setIntPref("ssl_port", 0);
                }
            }
        }
        catch (e) {
            Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("FiddlerHook Error when taking over configuration: " + e.message);
        }

        // Apply the user's chosen Fiddler-bypass list, if present
        var strBypass = this.prefsHook.getCharPref("bypasslist");
        this.prefsProxy.setCharPref("no_proxies_on", strBypass);

        // TODO: Probably ought to save this to restore it later...
        Services.prefs.setIntPref("network.http.max-persistent-connections-per-proxy", 32);  // Default is 8 in old FF, and 32 in new FF.
    },

    doDetach: function () {
        if (null == this.prefsProxy) return; // Assert?

        // If we're not attached to Fiddler, then we have nothing to do.
        if ((this.prefsProxy.getIntPref("type") != 1) ||
            (this.prefsProxy.getCharPref("http") != "127.0.0.1") ||
            (this.prefsProxy.getIntPref("http_port") != this.iFiddlerPort)) {
            return;
        }

        if ((this.prefsHook.getIntPref("backup-proxytype") == 1) &&
            (this.prefsHook.getCharPref("backup-proxyhttphost") == "127.0.0.1") &&
            (this.prefsHook.getIntPref("backup-proxyhttpport") == this.iFiddlerPort)) {
            Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("Backup proxy settings also pointed at Fiddler. Assuming incorrect and setting proxy to SYSTEM.");

            // Wipe backup-proxytype / backup-proxyhttphost / backup-proxyport as they are pointed at garbage.
            try { this.prefsHook.clearUserPref("backup-proxytype"); } catch (e) { }
            try { this.prefsHook.clearUserPref("backup-proxyhttphost"); } catch (e) { }
            try { this.prefsHook.clearUserPref("backup-proxyhttpport"); } catch (e) { }

            // Reset to System proxy
            this.prefsProxy.setIntPref("type", 5);
            this.prefsProxy.setCharPref("http", "");
            this.prefsProxy.setCharPref("socks", "");
            this.prefsProxy.setIntPref("http_port", 0);
            this.prefsProxy.setCharPref("ssl", "");
            this.prefsProxy.setIntPref("ssl_port", 0);
        }
        else {
            // Revert to prior proxy setting
            this.prefsProxy.setIntPref("type", this.prefsHook.getIntPref("backup-proxytype"));
            this.prefsProxy.setCharPref("http", this.prefsHook.getCharPref("backup-proxyhttphost"));
            this.prefsProxy.setCharPref("socks", this.prefsHook.getCharPref("backup-proxysockshost"));
            this.prefsProxy.setIntPref("http_port", this.prefsHook.getIntPref("backup-proxyhttpport"));

            // Only revert the SSL one if we set a backup?
            this.prefsProxy.setCharPref("ssl", this.prefsHook.getCharPref("backup-proxysslhost"));
            this.prefsProxy.setIntPref("ssl_port", this.prefsHook.getIntPref("backup-proxysslport"));
        }

        // TODO: Revert these properly if needed...
        //	var prefManager = Components.classes["@mozilla.org/preferences-service;1"].getService(Components.interfaces.nsIPrefBranch);
        // prefManager.setIntPref("network.http.max-persistent-connections-per-proxy", ***oldVal***);

        // Revert the bypass list
        this.prefsProxy.setCharPref("no_proxies_on", this.prefsHook.getCharPref("backup-no_proxies_on"));  // http://kb.mozillazine.org/Network.proxy.no_proxies_on
    },

    //
    // This function executes if the user pushes the "Launch Fiddler" toolbar button.
    //
    onToolbarButtonCommand: function (e) {
        // https://developer.mozilla.org/en/Code_snippets/Running_applications
        var file = Components.classes["@mozilla.org/file/local;1"].createInstance(Components.interfaces.nsILocalFile);
        var sFiddlerPath;

        try {
            // https://developer.mozilla.org/En/Accessing_the_Windows_Registry_Using_XPCOM
            var wrk = Components.classes["@mozilla.org/windows-registry-key;1"].createInstance(Components.interfaces.nsIWindowsRegKey);
            wrk.open(wrk.ROOT_KEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft", wrk.ACCESS_READ);
            var subkey = wrk.openChild("Fiddler2", wrk.ACCESS_READ);
            sFiddlerPath = subkey.readStringValue("InstallPath");
            subkey.close();
            wrk.close();
        }
        catch (e) {
            sFiddlerPath = "C:\\Program Files\\Fiddler2";
        }

        sFiddlerPath = (sFiddlerPath + "\\fiddler.exe");
        try {
            // Components.classes["@mozilla.org/consoleservice;1"].getService(Components.interfaces.nsIConsoleService).logStringMessage("Fiddler Path: " + sFiddlerPath);
            file.initWithPath(sFiddlerPath);
            // TODO: Can we/should we pass in the current process ID?
            file.launch();
        }
        catch (e) {
            Components.classes["@mozilla.org/embedcomp/prompt-service;1"].getService(Components.interfaces.nsIPromptService).alert(window, "Error", sFiddlerPath + " could not be run.\n" + e.message);
        }
    },
    onCertImport: function (e) {
        try {
            var certdb = Components.classes["@mozilla.org/security/x509certdb;1"].getService(Components.interfaces.nsIX509CertDB);
            var file = Components.classes["@mozilla.org/file/directory_service;1"].getService(Components.interfaces.nsIProperties).
                get("Desk", Components.interfaces.nsIFile);
            file.append("FiddlerRoot.cer");

            if (!file.exists()) {
                var nsIFilePicker = Components.interfaces.nsIFilePicker;
                var fp = Components.classes["@mozilla.org/filepicker;1"].createInstance(nsIFilePicker);
                fp.init(window, "Select FiddlerRoot.cer", nsIFilePicker.modeOpen);
                fp.appendFilter("Certificate Files", "*.cer");
                var res = fp.show();
                if (res == nsIFilePicker.returnCancel) { return; }
                file = fp.file;
            }
        }
        catch (e) { alert("Failed to find certificate.\n\n" + e); }

        try {
            alert("On the following screen, tick the first checkbox: 'Trust this CA to identify websites.'");
            certdb.importCertsFromFile(null, file, Components.interfaces.nsIX509Cert.CA_CERT);
        }
        catch (e) { alert("Trust function returned:\n\n" + e); }
    },
    onClearCacheCommand: function (e) {
        try {
            var oCacheService = Components.classes["@mozilla.org/network/cache-service;1"].getService(Components.interfaces.nsICacheService);
            oCacheService.evictEntries(Components.interfaces.nsICache.STORE_ON_DISK);
            oCacheService.evictEntries(Components.interfaces.nsICache.STORE_IN_MEMORY);
        }
        catch (exception) {
            try {
                var cache = Components.classes["@mozilla.org/netwerk/cache-storage-service;1"].getService(Components.interfaces.nsICacheStorageService);
                cache.clear();
                var imageCache = Components.classes["@mozilla.org/image/tools;1"].getService(Components.interfaces.imgITools).getImgCacheForDocument(null);
                imageCache.clearCache(false); //  false=content
                Components.utils.import("resource:///modules/offlineAppCache.jsm");
                OfflineAppCacheHelper.clear();
            }
            catch (ex2) {
                alert("Failed to clear Cache: " + exception.message + "\n" + ex2.message);
            } 
        }
    },
    onClearCookiesCommand: function (e) {
        try {
            Components.classes["@mozilla.org/cookiemanager;1"]
               .getService(Components.interfaces.nsICookieManager).removeAll();
        }
        catch (exception) {
            alert("Failed to Clear Cookies: " + exception.message);
        }
    }
};

window.addEventListener("load", function(e) { fiddlerhook.onLoad(e); }, false);
window.addEventListener("unload", function(e) { fiddlerhook.onUnload(e); }, false);