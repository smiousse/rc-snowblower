
# Make the kernel output less verbose by adding the "quiet" flag to the kernel command line in file /boot/cmdline.txt 

sudo nano /boot/cmdline.txt :            
dwc_otg.lpm_enable=0 console=serial0,115200 console=tty1 root=PARTUUID=32e07f87-02 rootfstype=ext4 elevator=deadline fsck.repair=yes quiet rootwait

# Optimize booting
sudo nano /boot/config.txt :
disable_splash=1
dtoverlay=pi3-disable-bt
dtoverlay=pi3-disable-wifi
dtoverlay=sdtweak,overclock_50=100
boot_delay=0
force_turbo=1
dtparam=audio=off

# Disable HDMI
sudo nano /etc/rc.local

/usr/bin/tvservice -o

# Disable these service
sudo systemctl disable avahi-daemon.service
sudo systemctl disable triggerhappy.service
sudo systemctl disable raspi-config.service
sudo systemctl disable apt-daily.service
sudo systemctl disable apt-daily.timer
sudo systemctl disable nfs-client.target
sudo systemctl disable apt-daily-upgrade.timer
sudo systemctl disable nfs-config.service
sudo systemctl disable remote-fs.target
sudo systemctl disable keyboard-setup.service
sudo systemctl disable hciuart.service
sudo systemctl disable wpa_supplicant.service

sudo apt-get purge --remove plymouth

# Remove the mount on boot partition
sudo nano /etc/fstab 

# Set fix ip address
sudo nano /etc/dhcpcd.conf

interface eth0
static ip_address=192.168.2.14/24
static routers=192.168.2.1
static domain_name_servers=192.168.2.1


# Checking boot time 

systemd-analyze 

systemd-analyze blame


# Sources : 
https://himeshp.blogspot.com/2018/08/fast-boot-with-raspberry-pi.html
https://raspberrypi.stackexchange.com/questions/37920/how-do-i-set-up-networking-wifi-static-ip-address-on-raspbian-raspberry-pi-os/74428#74428

