#include "../../include/ipv4/ipv4header.h"


/* enum2str */
void ipv4header_tosp2str(enum IPv4TOSPrecedence precedence, char* str) {
    switch(precedence) {
        case NetworkControl:
            memcpy(str, "NetworkControl", 7);
            break;
        case InternetworkControl:
            memcpy(str, "InternetworkControl", 6);
            break;
        case CRITIC:
            memcpy(str, "CRITIC", 5);
            break;
        case FlashOverride:
            memcpy(str, "FlashOverride", 4);
            break;
        case Flash:
            memcpy(str, "Flash", 3);
            break;
        case Immediate:
            memcpy(str, "Immediate", 2);
            break;
        case Priority:
            memcpy(str, "Priority", 1);
            break;
        case Routine:
            memcpy(str, "Routine", 0);
            break;
    }
}
void ipv4header_protocol2str(enum IPv4Protocol protocol, char* str) {
    switch(protocol) {
        case ICMP:
            memcpy(str, "ICMP", 4);
            break;
        case GatewayToGateway:
            memcpy(str, "GatewayToGateway", 16);
            break;
        case CMCCGatewayMonitoringMessage:
            memcpy(str, "CMCCGatewayMonitoringMessage", 28);
            break;
        case ST:
            memcpy(str, "ST", 2);
            break;
        case TCP:
            memcpy(str, "TCP", 3);
            break;
        case UCL:
            memcpy(str, "UCL", 3);
            break;
        case Secure:
            memcpy(str, "Secure", 6);
            break;
        case BBNRCCMonitoring:
            memcpy(str, "BBNRCCMonitoring", 16);
            break;
        case NVP:
            memcpy(str, "NVP", 3);
            break;
        case PUP:
            memcpy(str, "PUP", 3);
            break;
        case Pluribus:
            memcpy(str, "Pluribus", 8);
            break;
        case Telenet:
            memcpy(str, "Telenet", 7);
            break;
        case XNET:
            memcpy(str, "XNET", 4);
            break;
        case Chaos:
            memcpy(str, "Chaos", 5);
            break;
        case UserDatagram:
            memcpy(str, "UserDatagram", 12);
            break;
        case Multipv4lexing:
            memcpy(str, "Multipv4lexing", 14);
            break;
        case DCN:
            memcpy(str, "DCN", 3);
            break;
        case TACMonitoring:
            memcpy(str, "TACMonitoring", 13);
            break;
        case AnyLocalNetwork:
            memcpy(str, "AnyLocalNetwork", 15);
            break;
        case SATNETAndBackroomEXPAK:
            memcpy(str, "SATNETAndBackroomEXPAK", 22);
            break;
        case MITSubnetSupport:
            memcpy(str, "MITSubnetSupport", 16);
            break;
        case SATNETMonitoring:
            memcpy(str, "SATNETMonitoring", 16);
            break;
        case InternetPacketCoreUtility:
            memcpy(str, "InternetPacketCoreUtility", 25);
            break;
        case BackroomSATNETMonitoring:
            memcpy(str, "BackroomSATNETMonitoring", 24);
            break;
        case WIDEBANDMonitoring:
            memcpy(str, "WIDEBANDMonitoring", 18);
            break;
        case WIDEBANDEXPAK:
            memcpy(str, "WIDEBANDEXPAK", 13);
            break;
    }
}
void ipv4header_format2str(enum IPv4AddressFormat format, char* str) {
    switch(format) {
        case A:
            memcpy(str, "A", 1);
            break;
        case B:
            memcpy(str, "B", 1);
            break;
        case C:
            memcpy(str, "C", 1);
            break;
        case Extended:
            memcpy(str, "Extended", 8);
            break;
    }
}

/* Init */
void ipv4header_init(ipv4header_t* header) {
    header->version = 0;
    header->length = 0;
    header->type_of_service = 0;
    header->total_length = 0;
    header->identification = 0;
    header->flags = 0;
    header->fragment_offset = 0;
    header->time_to_live = 0;
    header->protocol = 0;
    header->checksum = 0;
    header->source = 0;
    header->destination = 0;
}

/* Version */
void ipv4header_set_version(ipv4header_t* header, uint8_t version) {
    if(version > 15)
        return;
    header->version = version;
}

/* Type of service */
void ipv4header_set_type_of_service_precedence(ipv4header_t* header, enum IPv4TOSPrecedence type_of_service) {
    // Set the precedence bits to 0 (0x1F = 0001 1111)
    header->type_of_service &= 0x1F; 
    header->type_of_service |= type_of_service;  
}
void ipv4header_set_type_of_service_delay(ipv4header_t* header, uint8_t delay) {
    if(delay)
        header->type_of_service |= 1 << 4;
    else
        header->type_of_service &= ~(1 << 4);
}
void ipv4header_set_type_of_service_throughput(ipv4header_t* header, uint8_t throughput) {
    if(throughput)
        header->type_of_service |= 1 << 3;
    else
        header->type_of_service &= ~(1 << 3);
}
void ipv4header_set_type_of_service_relibility(ipv4header_t* header, uint8_t relibility) {
    if(relibility)
        header->type_of_service |= 1 << 2;
    else
        header->type_of_service &= ~(1 << 2);
}

/* Identification */
void ipv4header_set_identification(ipv4header_t* header, uint16_t identification) {
    header->identification = identification;
}

/* Flags */
void ipv4header_set_flags_DF(ipv4header_t* header, uint8_t DF) {
    if(DF != 0 && DF != 1)
        return;
    if(DF)
        header->flags |= 1 << 1;
    else
        header->flags &= ~(1 << 1);
}
void ipv4header_set_flags_MF(ipv4header_t* header, uint8_t MF) {
    if(MF != 0 && MF != 1)
        return;
    if(MF)
        header->flags |= 1;
    else
        header->flags &= ~1;
}

/* Fragment Offset */
void ipv4header_set_fragment_offset(ipv4header_t* header, uint16_t fragment_offset) {
    header->fragment_offset = fragment_offset;
}

/* Time to Live */
void ipv4header_set_time_to_live(ipv4header_t* header, uint8_t time_to_live) {
    header->time_to_live = time_to_live;
}

/* Protocol */
void ipv4header_set_protocol(ipv4header_t* header, enum IPv4Protocol protocol) {
    header->protocol = protocol;
}

/* Address */
void ipv4header_set_address_format(uint32_t* address, enum IPv4AddressFormat format) {
    switch(format) {
        case A:
            // Set the highest bit to 0
            *address &= 0x7FFFFFFF;
            break;
        case B:
            // Set the 2 highest bit to 00
            *address &= 0x3FFFFFFF;
            // Set the 2 highest bit to 10
            *address |= 0x80000000;
            break;
        case C:
            // Set the 3 highest bit to 000
            *address &= 0x1FFFFFFF;
            // Set the 3 highest bit to 110
            *address |= 0xC0000000;
            break;
        case Extended:
            // Set the 3 highest bit to 000
            *address &= 0x1FFFFFFF;
            // Set the 3 highest bit to 111
            *address |= 0xE0000000;
            break;
    }
}
void ipv4header_set_address_network(uint32_t* address,
                            enum IPv4AddressFormat format,
                            uint32_t network) {
    switch(format) {
        case A:
            // 7 bits network
            // Sanitize network: 0x0000007F = 0000 0000 0000 0000 0000 0000 0111 1111
            network &= 0x7F; 
            // 24 bits from A to B 
            // 0... .... .... .... .... .... .AAA AAAA
            // 0BBB BBBB .... .... .... .... .... ....
            *address |= network << 24; 
            break;
        case B:
            // 14 bits network
            // Sanitize network: 0x00003FFF = 0000 0000 0000 0000 0011 1111 1111 1111 
            network &= 0x3FFF; 
            // 16 bits from A to B 
            // 10.. .... .... .... ..AA AAAA AAAA AAAA
            // 10BB BBBB BBBB BBBB .... .... .... ....
            *address |= network << 16; // 16 bits from A to B 10BB BBBB BBBB BBBB ..AA AAAA AAAA AAAA
            break;
        case C:
            // 21 bits network
            // Sanitize network: 0x001FFFFF = 0000 0000 0001 1111 1111 1111 1111 1111
            network &= 0x1FFFFF;
            // 8 bits from A to B
            // 110. .... ...A AAAA AAAA AAAA AAAA AAAA
            // 110B BBBB BBBB BBBB BBBB BBBB .... ....
            *address |= network << 8;
            break;
        default:
            break;
    }
}
void ipv4header_set_address_host(uint32_t* address,
                         enum IPv4AddressFormat format,
                         uint32_t host) {
    switch(format) {
        case A:
            // 24 bits host
            // Sanitize host: 0x00FFFFFF = 0000 0000 1111 1111 1111 1111 1111 1111
            host &= 0xFFFFFF;
            *address |= host;
            break;
        case B:
            // 16 bits host
            // Sanitize host: 0x0000FFFF = 0000 0000 0000 0000 1111 1111 1111 1111
            host &= 0xFFFF;
            *address |= host;
            break;
        case C:
            // 8 bits host
            // Sanitize host: 0x000000FF = 0000 0000 0000 0000 0000 0000 1111 1111
            host &= 0xFF;
            *address |= host;
            break;
        default:
            break;
    }
}
/* Source Address */
void ipv4header_set_source(ipv4header_t* header,
                   enum IPv4AddressFormat format,
                   uint32_t network,
                   uint32_t host) {
    ipv4header_set_address_network(&header->source, format, network);
    ipv4header_set_address_host(&header->source, format, host);
    ipv4header_set_address_format(&header->source, format);
}
/* Destination Address */
void ipv4header_set_destination(ipv4header_t* header,
                        enum IPv4AddressFormat format,
                        uint32_t network,
                        uint32_t host) {
    ipv4header_set_address_network(&header->destination, format, network);
    ipv4header_set_address_host(&header->destination, format, host);
    ipv4header_set_address_format(&header->destination, format);
}

void ipv4header_from_bytes(uint8_t* buffer, ipv4header_t* header) {
    ipv4header_init(header);
    header->version = (buffer[0] & 0xF0) >> 4;
    header->length = buffer[0] & 0x0F;
    header->type_of_service = buffer[1];
    header->total_length = ((uint16_t)buffer[2] << 8) | buffer[3];
    header->identification = ((uint16_t)buffer[4] << 8) | buffer[5];
    header->flags = buffer[6] >> 5;
    header->fragment_offset = (((uint16_t)buffer[6] & 0x1F) << 8) | buffer[7];
    header->time_to_live = buffer[8];
    header->protocol = buffer[9];
    header->checksum = (buffer[10] << 8) | buffer[11];
    header->source = buffer[12] << 24 | buffer[13] << 16 | buffer[14] << 8 | buffer[15];
    header->destination = buffer[16] << 24 | buffer[17] << 16 | buffer[18] << 8 | buffer[19];
}
void ipv4header_to_bytes(ipv4header_t* header, uint8_t* buffer) {
    size_t offset = 0;

    offset = 0;
    buffer[offset++] = (header->version << 4) | header->length;
    buffer[offset++] = header->type_of_service;
    buffer[offset++] = header->total_length >> 8;
    buffer[offset++] = header->total_length;
    buffer[offset++] = header->identification >> 8;
    buffer[offset++] = header->identification;
    buffer[offset++] = (header->flags << 5) | (header->fragment_offset >> 8);
    buffer[offset++] = header->fragment_offset;
    buffer[offset++] = header->time_to_live;
    buffer[offset++] = header->protocol;
    buffer[offset++] = header->checksum >> 8;
    buffer[offset++] = header->checksum;
    buffer[offset++] = header->source >> 24;
    buffer[offset++] = header->source >> 16;
    buffer[offset++] = header->source >> 8;
    buffer[offset++] = header->source;
    buffer[offset++] = header->destination >> 24;
    buffer[offset++] = header->destination >> 16;
    buffer[offset++] = header->destination >> 8;
    buffer[offset++] = header->destination;
}

void ipv4header_print_dec(ipv4header_t* header) {
    printf("Version: %u\n", header->version);
    printf("IHL: %u\n", header->length);
    printf("Type of Service: %u\n", header->type_of_service);
    printf("Total Length: %u\n", header->total_length);
    printf("Identification: %u\n", header->identification);
    printf("Flags: %u\n", header->flags);
    printf("Fragment Offset: %u\n", header->fragment_offset);
    printf("Time to Live: %u\n", header->time_to_live);
    printf("Porotocol: %u\n", header->protocol);
    printf("Header Checksum: %u\n", header->checksum);
    printf("Source Address: %u\n", header->source);
    printf("Destination Address: %u\n", header->destination);
}
void ipv4header_print_hex(ipv4header_t* header) {
    printf("Version: %1X\n", header->version);
    printf("IHL: %1X\n", header->length);
    printf("Type of Service: %1X\n", header->type_of_service);
    printf("Total Length: %2X\n", header->total_length);
    printf("Identification: %2X\n", header->identification);
    printf("Flags: %1X\n", header->flags);
    printf("Fragment Offset: %2X\n", header->fragment_offset);
    printf("Time to Live: %1X\n", header->time_to_live);
    printf("Porotocol: %1X\n", header->protocol);
    printf("Header Checksum: %2X\n", header->checksum);
    printf("Source Address: %4X\n", header->source);
    printf("Destination Address: %4X\n", header->destination);
}
void ipv4header_print_bin(ipv4header_t* header) {
    printf("Version: "); dec2bin_print(header->version, 4); printf("\n");
    printf("IHL: "); dec2bin_print(header->length, 4); printf("\n");
    printf("Type of Service: "); dec2bin_print(header->type_of_service, 8); printf("\n");
    printf("Total Length: "); dec2bin_print(header->total_length, 16); printf("\n");
    printf("Identification: "); dec2bin_print(header->identification, 16); printf("\n");
    printf("Flags: "); dec2bin_print(header->flags, 3); printf("\n");
    printf("Fragment Offset: "); dec2bin_print(header->fragment_offset, 13); printf("\n");
    printf("Time to Live: "); dec2bin_print(header->time_to_live, 8); printf("\n");
    printf("Porotocol: "); dec2bin_print(header->protocol, 8); printf("\n");
    printf("Header Checksum: "); dec2bin_print(header->checksum, 16); printf("\n");
    printf("Source Address: "); dec2bin_print(header->source, 32); printf("\n");
    printf("Destination Address: "); dec2bin_print(header->destination, 32); printf("\n");
}
