
    ***Installation instructions***

1.  https://chromedriver.chromium.org/downloads
    Both the browser and the driver must have the same version for compatibility.

    dfn install google-chrome-stable chromedriver
    
2. pip3 install selenium
   pip3 install requests
   
3. Debugging with pycharm will require to disable sudo password
   username ALL=(ALL) NOPASSWD:ALL
   
4. Cyberghost binary creates the tun device but the connection is dead.
   To solve it follow this tutorial:
   https://support.cyberghostvpn.com/hc/en-us/articles/360007929314-How-to-Set-Up-OpenVPN-on-Linux-Ubuntu-via-Network-Manager
   
   Configure new device (Other) w/ Protocol=openvpn, Country=Italy, Server Group=TCP (not UDP)
   Download configuration files, unzip and copy to VPN_CYBERGHOST [ca.crt, client.crt, client.key, openvpn.ovpn]
   Copy user, pass and save them in pass.txt
   Change openvpn.ovpn, add full path for ca,cert,key and after line 'proto tcp' add auth-user-pass 'path to pass.txt'.
   
5. Check util.py:29  CAPTCH_API_KEY=""


