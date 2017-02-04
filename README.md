# CDP Splitter

[Ciholas Data Protocol (CDP)](http://www.ciholas.com/downloads/dwusb/CDP-2016.08.15.pdf) is a UDP based protocol that allows for transport of data items.  CDP was invented by [Ciholas, Inc](http://www.ciholas.com) as a standard for communication with the [CUWB Location System](http://www.ciholas.com/dwusb/).

The CDP Splitter allows users to receive CDP Data Items and rebroadcast them to a different IP and port.  The CDP Splitter serves as example C code for receiving CDP Packets and Data Items.

## Download

Download the source or clone it from git.

## Building

You will need rake and gcc tools to build the software.

In Ubuntu:
```bash
sudo apt-get install rake build-essential
```

Then to build, run rake.
```bash
rake source
```

The binary will be available in `output/cdp-splitter`

## Usage

Run the CDP Splitter from the root of the source directory with the following.
```bash
./output/cdp-splitter IFC IP PORT CSV
```
* IFC is the name of the interface to listen for the input on (ie: lo, or eth0)
* IP is the ip address to listen on (ie: 239.255.76.67)
* PORT is the port number to listen on (ie: 7667)
* CSV is the path to a CSV file with destination IP and ports in it (see [example](example.csv))

The IFC, IP, and PORT can be best determined by looking at the settings for your CUWB Server's external interface.

# License

The CDP Splitter is licensed under [creativecommons.org/licenses/by/4.0](http://creativecommons.org/licenses/by/4.0).

To satisfy the license, please leave the Ciholas, Inc. line in the top of all sources files.  Any files that are modified should be noted that they are not the originals.

# Support

Please post any issues to the GitHub issues page.

Email for further questions to cuwb(dot)support(at)ciholas(dot)com.
