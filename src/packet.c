#include <stdlib.h>
#include <string.h>
#include "../include/packet.h"

disco_packet_header packet_header(packet_types type, encodings encoding, short retain, short duplicate) {
    disco_packet_header header;
    header.bits.type = type;
    header.bits.encoding = encoding;
    header.bits.retain = retain;
    header.bits.duplicate = duplicate;
    return header;
}

disco_BORN born_packet(unsigned cluster_tag) {
    disco_BORN packet;
    packet.header = packet_header(BORN, UNDEFINED, 0, 0);
    packet.payload.cluster_tag = cluster_tag;
    return packet;
}

disco_GREET greet_packet(short duplicate) {
    disco_GREET packet;
    packet.header = packet_header(GREET, UNDEFINED, 0, duplicate);
    return packet;
}

disco_GREET_ACK greet_ack_packet(short duplicate) {
    disco_GREET_ACK packet;
    packet.header = packet_header(GREET_ACK, UNDEFINED, 0, duplicate);
    return packet;
}

disco_HEARTBEAT heartbeat_packet() {
    disco_HEARTBEAT packet;
    packet.header = packet_header(HEARTBEAT, UNDEFINED, 0, 0);
    return packet;
}

disco_DEAD dead_packet(unsigned cluster_tag) {
    disco_DEAD packet;
    packet.header = packet_header(DEAD, UNDEFINED, 0, 0);
    packet.payload.cluster_tag = cluster_tag;
    return packet;
}

disco_SERVE serve_packet(const char* service_name, char* raw_data, encodings encoding, short duplicate) {
    disco_SERVE packet;
    packet.header = packet_header(SERVE, encoding, 0, duplicate);
    packet.payload.service_name = (char*) malloc(strlen(service_name));
    packet.payload.raw_data = (char*) malloc(strlen(raw_data));
    strcpy(packet.payload.service_name, service_name);
    strcpy(packet.payload.raw_data, raw_data);
    return packet;
}

disco_SERVE_RESP serve_resp_packet(char* raw_response, encodings encoding, short duplicate) {
    disco_SERVE_RESP packet;
    packet.header = packet_header(SERVE_RESP, encoding, 0, duplicate);
    packet.payload.raw_response = (char*) malloc(strlen(raw_response));
    strcpy(packet.payload.raw_response, raw_response);
    return packet;
}

disco_GET get_packet(unsigned key, short duplicate) {
    disco_GET packet;
    packet.header = packet_header(GET, UNDEFINED, 0, duplicate);
    packet.payload.key = key;
    return packet;
}

disco_GET_RESP get_resp_packet(char* raw_response, encodings encoding, short duplicate) {
    disco_GET_RESP packet;
    packet.header = packet_header(GET_RESP, encoding, 0, duplicate);
    packet.payload.raw_response = (char*) malloc(strlen(raw_response));
    strcpy(packet.payload.raw_response, raw_response);
    return packet;
}

disco_SET set_packet(unsigned key, char* raw_data, encodings encoding, short retain, short duplicate) {
    disco_SET packet;
    packet.header = packet_header(SET, UNDEFINED, retain, duplicate);
    packet.payload.key = key;
    packet.payload.raw_data = (char*) malloc(strlen(raw_data));
    strcpy(packet.payload.raw_data, raw_data);
    return packet;
}

disco_SET_RESP set_resp_packet(unsigned success, short duplicate) {
    disco_SET_RESP packet;
    packet.header = packet_header(SET_RESP, UNDEFINED, 0, duplicate);
    packet.payload.bits.success = success;
    return packet;
}

disco_MESSAGE message_packet(char* raw_message, encodings encoding, short retain, short duplicate) {
    disco_MESSAGE packet;
    packet.header = packet_header(MESSAGE, UNDEFINED, retain, duplicate);
    packet.payload.raw_message = (char*) malloc(strlen(raw_message));
    strcpy(packet.payload.raw_message, raw_message);
    return packet;
}

disco_MESSAGE_ACK message_ack_packet(unsigned success, short duplicate) {
    disco_MESSAGE_ACK packet;
    packet.header = packet_header(MESSAGE_ACK, UNDEFINED, 0, duplicate);
    packet.payload.bits.success = success;
    return packet;
}