import sys
import can

def main() -> int:
    """
    Main function to test the SLCAN interface using python-can library.
    """
    bus = can.interface.Bus(interface='slcan', channel='COM5', bitrate=250000)

    version = bus.get_version(1)
    serial_number = bus.get_serial_number(1)
    print(version)
    assert version == (1,1) # Expected version tuple

    print(serial_number)
    assert serial_number == 'NT32' # Expected serial number

    bus.shutdown()

    return 0

if __name__ == "__main__":
    sys.exit(main())