#include <string.h>
#include "../include/packet.h"

/**
 * @brief Get the packet header object
 * 
 * @param type 
 * @param encoding 
 * @param retain 
 * @param duplicate 
 * @return disco_packet_header 
 */
disco_packet_header packet_header(packet_types type, encodings encoding, short retain, short duplicate) {
    disco_packet_header header;
    header.bits.type = type;
    header.bits.encoding = encoding;
    header.bits.retain = retain;
    header.bits.duplicate = duplicate;
    return header;
}

disco_BORN born_packet(unsigned char cluster_tag[CLUSTER_TAG_LENGTH]) {
    disco_BORN packet;
    packet.header = packet_header(BORN, UNDEFINED, 0, 0);
    for (int idx=0; idx<CLUSTER_TAG_LENGTH; idx++) {
        packet.cluster_tag[idx] = cluster_tag[idx];
    }
    return packet;
}

disco_GREET greet_packet(int duplicate) {
    disco_GREET packet;
    packet.header = packet_header(GREET, UNDEFINED, 0, duplicate);
    return packet;
}

disco_GREET_ACK greet_ack_packet(int duplicate) {
    disco_GREET_ACK packet;
    packet.header = packet_header(GREET_ACK, UNDEFINED, 0, duplicate);
    return packet;
}

disco_HEARTBEAT heartbeat_packet() {
    disco_HEARTBEAT packet;
    packet.header = packet_header(HEARTBEAT, UNDEFINED, 0, 0);
    return packet;
}

disco_DEAD dead_packet(unsigned char cluster_tag[CLUSTER_TAG_LENGTH]) {
    disco_DEAD packet;
    packet.header = packet_header(DEAD, UNDEFINED, 0, 0);
    for (int idx=0; idx<CLUSTER_TAG_LENGTH; idx++) {
        packet.cluster_tag[idx] = cluster_tag[idx];
    }
    return packet;
}