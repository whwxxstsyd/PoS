LDIR= -L ../lib/  -lGL14epos
IDIR=../include/
LDFLAGS=-pthread
#CC=arm-none-linux-gnueabi-gcc   
CC=/opt/freescale/usr/local/gcc-4.1.2-glibc-2.5-nptl-3/arm-none-linux-gnueabi/bin/arm-none-linux-gnueabi-gcc  

OBJS=main_menu.o scroll_menu.o lcd.o keypad.o setup.o battery.o print.o  usb.o download.o console.o local.o massstorage.o machineid.o jffs2.o version.o rfid.o communication.o ethernet.o gsm_gprs.o  wifi.o ppp_api.o pppcomm.o  V91Modem.o remote.o sdcard.o    imagesinfo.o usb_test.o    barcode.o  magnetic_head.o   sam.o ifd.o  audio.o log.o irda.o

test_apl:$(OBJS)
	$(CC) -o app  $(OBJS) $(LDIR) $(LDFLAGS) -w -O2  

main_menu.o :main_menu.c 
	$(CC) -I $(IDIR) -c main_menu.c
scroll_menu.o:scroll_menu.c
	$(CC) -I $(IDIR) -c scroll_menu.c
lcd.o:lcd.c
	$(CC) -I $(IDIR) -c lcd.c
keypad.o:keypad.c
	$(CC) -I $(IDIR) -c keypad.c
print.o:print.c
	$(CC) -I $(IDIR) -c print.c
battery.o:battery.c
	$(CC) -I $(IDIR) -c battery.c
download.o:download.c
	$(CC) -I $(IDIR) -c download.c
console.o:console.c
	$(CC) -I $(IDIR) -c console.c
eposdatabase.o:eposdatabase.c
	$(CC) -I $(IDIR) -c eposdatabase.c
communication.o:communication.c
	$(CC) -I $(IDIR) -c communication.c
pstn.o:pstn.c
	$(CC) -I $(IDIR) -c pstn.c
ethernet.o:ethernet.c
	$(CC) -I $(IDIR) -c ethernet.c
gsm_gprs.o:gsm_gprs.c
	$(CC) -I $(IDIR) -c gsm_gprs.c
wifi.o:wifi.c
	$(CC) -I $(IDIR) -c wifi.c

ppp_api.o:ppp_api.c
	$(CC) -I $(IDIR) -c ppp_api.c
cdma.o:cdma.c
	$(CC) -I $(IDIR) -c cdma.c
usb.o:usb.c
	$(CC) -I $(IDIR) -c usb.c
local.o:local.c
	$(CC) -I $(IDIR) -c local.c
remote.o:remote.c
	$(CC) -I $(IDIR) -c remote.c
rfid.o:rfid.c
	$(CC) -I $(IDIR) -c rfid.c
jffs2.o:jffs2.c
	$(CC) -I $(IDIR) -c jffs2.c
machineid.o:machineid.c
	$(CC) -I $(IDIR) -c machineid.c
V91Modem.o:V91Modem.c
	$(CC) -I $(IDIR) -c V91Modem.c
setup.o:setup.c
	$(CC) -I $(IDIR) -c setup.c
sdcard.o:sdcard.c
	$(CC) -I $(IDIR)  -c sdcard.c
kermapi.o:kermapi.c
	$(CC) -I $(IDIR)  -c kermapi.c 
pppcomm.o:pppcomm.c
	$(CC) -I $(IDIR)  -c pppcomm.c
massstorage.o:massstorage.c
	$(CC) -I $(IDIR)  -c massstorage.c
version.o:version.c
	$(CC) -I $(IDIR)  -c version.c 
log.o:log.c
	$(CC) -I $(IDIR)  -c log.c
magnetic_head.o:magnetic_head.c
	$(CC) -I $(IDIR) -c magnetic_head.c
sam.o:sam.c
	$(CC) -I $(IDIR) -c sam.c
ifd.o:ifd.c
	$(CC) -I $(IDIR) -c ifd.c
imagesinfo.o:imagesinfo.c
	$(CC) -I $(IDIR)  -c imagesinfo.c 
usb_test.o:usb_test.c
	$(CC) -I $(IDIR) -c usb_test.c
barcode.o:barcode.c
	$(CC) -I $(IDIR) -c barcode.c
audio.o:audio.c
	$(CC) -I $(IDIR) -c audio.c
irda.o:irda.c
	$(CC) -I $(IDIR) -c irda.c

clean:
	rm -rf *.o 
	rm -rf app 
	rm -rf *.IMG
image:
	./newmkapp  app GL14-SD-APP-1031-3.5.IMG 
