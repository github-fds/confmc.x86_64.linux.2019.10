# CON-FMC<sup>TM</sup>
**CON-FMC** is an FMC (FPGA Mezzanine Card) and connects computer to the FPGA through USB 3.0/2.0.<br>
More details can be found at <a href="http://www.future-ds.com/en/products.html#CON_FMC" target="_blank">here</a>.
This page contains software package version 2019.10 for CON-FMC.
![CON-FMC board](doc/con-fmc-raspberry.png "CON-FMC")

## License
FUTURE DESIGN SYSTEMS SOFTWARE END-USER LICENSE AGREEMENT FOR CON-FMC.<br>
See '[EULA.txt](EULA.txt)' file.

## How to install
See '*Section 3 Software installation*' of '[doc/FDS-TD-2018-03-001-CON-FMC-User-Manual.pdf](doc/FDS-TD-2018-03-001-CON-FMC-User-Manual.pdf)'.

### Linux
 1. Get the package from GitHub, where '*2019.10*' stands for version<br>
   ```$ git clone https://github.com/github-fds/confmc.x86_64.linux.2019.10.git```
 2. Down to the retrieved directory<br>
   ```$ cd confmc.x86_64.linux.2019.10```
 3. Run '*coninstall.sh*' with root permission<br>
   ```$ sudo ./coninstall.sh```<br>
    Use '*-dst install_dir*' option to specify installation directory, otherwise '*/opt/confmc/2019.10*' will be used by default, where '*2019.10*' can be vary depending on version.
 4. Do not forget to source setup script before using this package<br>
    ```$ source /opt/confmc/2019.10/settings.sh```<br>
    Then, all necessary environment variables will be set for you.

### Windows
 1. Get the package from GitHub, where '*2019.10*' stands for version<br>
   ```> git clone https://github.com/github-fds/confmc.x86_64.mingw.2019.10.git```
 2. Copy the retrieved directory to somewhere<br>
   ```> copy confmc.x86_64.mingw.2019.10 C:\confmc\2019.10```
 3. Set '**CONFMC_HOME**' environment variable to '*C:\confmc\2019.10*'<br>
   ```> setx -m CONFMC_HOME C:\confmc\2019.10```

## How to use
Refer to following documents.<br>
* [doc/FDS-TD-2018-03-001-CON-FMC-User-Manual.pdf](doc/FDS-TD-2018-03-001-CON-FMC-User-Manual.pdf)
* [doc/FDS-TD-2018-04-004-CON-FMC-API.pdf](doc/FDS-TD-2018-04-004-CON-FMC-API.pdf)

Refer to examples available at <a href="https://github.com/github-fds/confmc.examples" target="_blank">here</a>.

## What's new
Refer to 'RELEASE_NOTES.txt'.

## Contact
* <a href="http://www.future-ds.com" target="_blank">**Future Design Systems**</a>
* **[contact@future-ds.com](mailto:contact@future-ds.com)**
