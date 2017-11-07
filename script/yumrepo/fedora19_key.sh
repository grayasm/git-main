#!/bin/bash

if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi

echo "Installing Fedora19 GPG Key"
cd /tmp
wget https://getfedora.org/static/FB4B18E6.txt
mv FB4B18E6.txt RPM-GPG-KEY-fedora-19-primary
cp /tmp/RPM-GPG-KEY-fedora-19-primary /etc/pki/rpm-gpg
chown -v root:root /etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-19-primary
chmod 644 /etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-19-primary
chcon -u system_u -t cert_t -v /etc/pki/rpm-gpg/RPM-GPG-KEY-fedora-19-primary
