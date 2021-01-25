# Lawicel Protocol

This Project implements the Protocol found in the [CAN232 Website](http://www.can232.com/docs/can232_v3.pdf).

# Changes to the Protocol

All the specified Commands specified in the Document are implemented and work as described. In addition to these, one command was added to get the current configuration of the system:

**D[CR]** 
Display System Information 
Returns: Dwxyz
* D: Display Settings Command
* w: Auto-start Status. 0=Deactivated, 1=Normal, 2=Listen Only
* x: CAN Baudrate. Follows same numeration as Sn[CR] Command
* y: Timestamp Status: 0=Deactivated, 1=Activated
* z: Channel Status. 0=Closed, 1=Normal, 2=Listen Only

 