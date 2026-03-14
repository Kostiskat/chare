# chare

###### (C + share) not related to chairs 🪑 <br> <br>

I am tired of transferring photos and files from my PC to other devices via the cloud. So I made this tool to do it locally.

It uses qrencode and web sockets to quickly send files from **Linux** to other devices on the network via sendfile. 

**Installation Instructions & How to Use:**
- Download the source code
- Run the installation script (located on ``scripts/install.sh``) This will build and install chare on ``/usr/local/bin/`` <br>
  **Note:** CMake *3.28 or above* must be installed.
- Open the Terminal (preferrably in the same directory that the file you want to share is)
- Run the command ``chare <filepath>``
- chare will create a local webserver which you can go to either by entering the IP on a browser, or scanning the displayed QR code with your phone

  

**Things to add:**
- Native support for more Operating Systems.
- and more features...

