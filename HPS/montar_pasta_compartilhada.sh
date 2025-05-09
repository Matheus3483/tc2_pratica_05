#!/bin/bash
LOCAL_PASTA="/var/tmp/de10standard"
IP_PLACA="root@10.42.0.81"
LOCAL_REMOTO="/home/root/tc2_fpga_pds/"
sudo sshfs -o allow_other,default_permissions $IP_PLACA:$LOCAL_REMOTO $LOCAL_PASTA
sudo chown -R $USER $LOCAL_PASTA
