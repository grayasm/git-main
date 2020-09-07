------------------------
cyberghost - 1.3.3
------------------------

Available arguments:


  SERVICES
    --service-type <serviceName>  : Select a service from list of services.
    --openvpn                     : Select OpenVPN as service.
    --wireguard                   : Select Wireguard as service.


  SERVER TYPES
    --server-type <serverType>    : Connect to specified server type. Available types: traffic, streaming and torrent. Default value: traffic.
    --traffic                     : Show only traffic countries.
    --streaming <serviceName>     : Get streaming service.
    --torrent                     : Show only torrent countries.


  OTHER COMMANDS
    --country-code <countryCode>  : Connect a specified country. If argument city is not set will be connected to random city from chosen country.
    --connection <connection>     : Set connection type for OpenVPN to UDP or TCP. Default value: UDP
    --city <cityName>             : Connect a specified city from a country.
    --server <serverName>         : Connect to a specified server.
    --connect                     : Prepare a new VPN connection.
    --status                      : Check if we have VPN connection opened.
    --stop                        : Terminate all VPN connection.
    --setup                       : Setup Cyberghost application.
    --uninstall                   : Uninstall Cyberghost application.



------------------------
    sudo uses wrong python version
    https://stackoverflow.com/questions/41135243/sudo-python-wrong-version
------------------------
    Install cyberghostvpn on Linux (Ubuntu)
    https://www.cyberghostvpn.com/en_US/support/articles/360020436274-How-to-install-the-CyberGhostVPN-CLI-App-on-Linux-
------------------------
    Use cyberghostvpn to connect to a specific server:
    https://www.cyberghostvpn.com/en_US/support/articles/360020673194--How-to-select-a-country-or-single-server-with-CyberGhost-on-Linux

    sudo cyberghostvpn --traffic --country-code IT --connection TCP
    sudo cyberghostvpn --traffic --country-code IT --connection TCP --city Milano
    sudo cyberghostvpn --traffic --country-code IT --connection TCP --city Rome

    sudo cyberghostvpn --traffic --country-code IT --connection TCP --city Milano --server milano-s403-i01 --connect
    84.17.58.2

    sudo cyberghostvpn --traffic --country-code IT --connection TCP --city Milano --server milano-s403-i02 --connect
    84.17.58.3

    sudo cyberghostvpn --traffic --country-code IT --connection TCP --city Milano --server milano-s403-i24 --connect
    84.17.58.25
------------------------

