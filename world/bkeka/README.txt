========================
    INSTALLATION
========================
1.  https://chromedriver.chromium.org/downloads
    Get the chromedriver version matching google-chrome-stable binary.
    chromedriver (epel) is not always synchronized with google-chrome-stable (google repo).
    Copy chromedriver in the project directory.

2. pip3 install selenium
   pip3 install requests

3. sudo in Pycharm debugger does not work.
   If you use the VPN connection then disable the password temporarily.
   username ALL=(ALL) NOPASSWD:ALL

4. Cyberghost binary creates the tun device but the connection is dead.
   To solve it follow this tutorial:
   https://support.cyberghostvpn.com/hc/en-us/articles/360007929314-How-to-Set-Up-OpenVPN-on-Linux-Ubuntu-via-Network-Manager

   Configure new device (Other) w/ Protocol=openvpn, Country=Italy, Server Group=TCP (not UDP)
   Download configuration files, unzip and copy to VPN_CYBERGHOST [ca.crt, client.crt, client.key, openvpn.ovpn]
   Copy user, pass and save them in pass.txt
   Change openvpn.ovpn, add full path for ca,cert,key and after line 'proto tcp' add auth-user-pass 'path to pass.txt'.

5. Check util.py:29  CAPTCH_API_KEY=""
6. Check default.cfg