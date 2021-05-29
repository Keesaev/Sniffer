# Sniffer
Simple Wireshark clone
## Features
* Capturing packets with libpcap
* Deserializing packets using factory pattern
* Presenting capture session with qml
* Combining c++ and qml with signal/slot system
* Serializing capture sessions with QFile
* Building charts based on collected stats with QChartView
## Screenshots
![](https://sun9-19.userapi.com/impg/5T0v9XrzlCrLqlGbWhUnf6U3wLaQvrxoELCQKg/0sYAtFAmp0A.jpg?size=1920x1080&quality=96&sign=3193dc05bc2bc1310c25cc79bebbfbbd&type=album)
![](https://sun9-18.userapi.com/impg/evH5398mzMKHruxXPklbBKhaFJkAYz_tpykV4Q/_pZB8f_VRJw.jpg?size=1000x638&quality=96&sign=d75594d654361a65b66c6289fedac4e0&type=album)
![](https://sun9-71.userapi.com/impg/W6nvRYn_XIxXbl4Y7X0bdn7ith6S1TJX8VleGQ/Yptj1LfC0Bs.jpg?size=703x520&quality=96&sign=1b2279aca4105fa50e5392aa641cffa3&type=album)
## Structure
* sniffer.cpp         - Everything to do with libpcap
* packet.cpp          - Member-only class containing packet data
* factory.cpp         - Factory class that works with basetransport and derived classes
* snifferwrapper.cpp  - A layer between c++ and qml that also works with threading
* packetmodel.cpp     - Class derived from QAbstractListModel to be used in PacketsView.qml as a model
### Protocols
* basetransport.cpp           - Base class for transport protocols
* network.cpp / dataling.cpp  - Representing levels of tcp/ip
* icmp.cpp / tcp.cpp / etc    - Representing transport protocol names
* unknowntransport.cpp        - Reprecenting transport protocols not to be deserialized
### Qml
* main.qml                    - Contains an instance of snifferwrapper, also represents a starting window
* DevicesListDelegate.qml     - Delegate for ListView in main.qml
* PacketsView.qml             - Represents second window (packet capture session)
* Other elements are used in PacketsView.qml
