#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>

#define CLUSTER_TAG_LENGTH 4
#define KEY_LENGTH         4

/* Packets - Bytes and Enumerations */

/* Discover Packets */
#define BORN_BYTE      0x00
#define GREET_BYTE     0x10
#define GREET_ACK_BYTE 0x20
#define HEARTBEAT_BYTE 0x30
#define DEAD_BYTE      0x40

/* Request Packets */
#define SERVE_BYTE 0x50
#define GET_BYTE   0x60
#define SET_BYTE   0x70

/* Response Packets */
#define SERVE_RESP_BYTE 0x80
#define GET_RESP_BYTE   0x90
#define SET_RESP_BYTE   0xA0

/* Message Packets */
#define MESSAGE_BYTE     0xB0
#define MESSAGE_ACK_BYTE 0xC0

typedef enum packet_types {
    BORN        = 0,
    GREET       = 1,
    GREET_ACK   = 2,
    HEARTBEAT   = 3,
    DEAD        = 4,
    SERVE       = 5,
    GET         = 6,
    SET         = 7,
    SERVE_RESP  = 8,
    GET_RESP    = 9,
    SET_RESP    = 10,
    MESSAGE     = 11,
    MESSAGE_ACK = 12
} packet_types;


/* Encodings - Bytes and Enumerations */

#define UTF_8_BYTE     0x00
#define UTF_16_BYTE    0x04
#define ASCII_BYTE     0x08
#define UNDEFINED_BYTE 0x0C

typedef enum encodings {
    UTF_8     = 0,
    UTF_16    = 1,
    ASCII     = 2,
    UNDEFINED = 3
} encodings;


/* HEADER Byte */

typedef union header {
    unsigned char byte;
    struct {
        unsigned duplicate : 1; // Duplicated or not
        unsigned retain    : 1; // Store this packet
        unsigned encoding  : 2; // Encoding
        unsigned type      : 4; // Packet type
    } bits;
} disco_packet_header;

disco_packet_header packet_header(packet_types type, encodings encoding, short retain, short duplicate);


/* BORN Packet */

typedef struct born {
    disco_packet_header header;
    union {
        unsigned char bytes[CLUSTER_TAG_LENGTH];
        unsigned cluster_tag : CLUSTER_TAG_LENGTH * 8;
    } payload;
} disco_BORN;

disco_BORN born_packet(unsigned cluster_tag);


/* GREET Packets */

typedef struct greet {
    disco_packet_header header;
} disco_GREET;

typedef struct greet_ack {
    disco_packet_header header;
} disco_GREET_ACK;

disco_GREET greet_packet(short duplicate);
disco_GREET_ACK greet_ack_packet(short duplicate);


/* HEARTBEAT Packet */

typedef struct hearbeat {
    disco_packet_header header;
} disco_HEARTBEAT;

disco_HEARTBEAT heartbeat_packet();


/* DEAD Packet */

typedef struct dead {
    disco_packet_header header;
    union {
        unsigned char bytes[CLUSTER_TAG_LENGTH];
        unsigned cluster_tag : CLUSTER_TAG_LENGTH * 8;
    } payload;
    
} disco_DEAD;

disco_DEAD dead_packet(unsigned cluster_tag);


/* SERVE Packets */

typedef struct serve {
    disco_packet_header header;
    struct {
        char* service_name;
        char* raw_data;
    } payload;
} disco_SERVE;

typedef struct serve_resp {
    disco_packet_header header;
    struct {
        char* raw_response;
    } payload;
} disco_SERVE_RESP;

disco_SERVE serve_packet(const char* service_name, char* raw_data, encodings encoding, short duplicate);
disco_SERVE_RESP serve_resp_packet(char* raw_response, encodings encoding, short duplicate);


/* GET Packets */

typedef struct get {
    disco_packet_header header;
    union {
        unsigned char bytes[KEY_LENGTH];
        unsigned key : KEY_LENGTH * 8;
    } payload;
} disco_GET;

typedef struct get_resp {
    disco_packet_header header;
    struct {
        char* raw_response;
    } payload;
} disco_GET_RESP;

disco_GET get_packet(unsigned key, short duplicate);
disco_GET_RESP get_resp_packet(char* raw_response, encodings encoding, short duplicate);


/* SET Packets */

typedef struct set {
    disco_packet_header header;
    struct {
        unsigned key : KEY_LENGTH * 8;
        char* raw_data;
    } payload;
} disco_SET;

typedef struct set_resp {
    disco_packet_header header;
    union {
        unsigned char byte;
        struct {
            unsigned reserved : 7;
            unsigned success  : 1;
        } bits;
    } payload;
} disco_SET_RESP;

disco_SET set_packet(unsigned key, char* raw_data, encodings encoding, short retain, short duplicate);
disco_SET_RESP set_resp_packet(unsigned success, short duplicate);


/* MESSAGE Packets */

typedef struct message {
    disco_packet_header header;
    struct {
        char* raw_message;
    } payload;
} disco_MESSAGE;

typedef struct message_resp {
    disco_packet_header header;
    union {
        unsigned char byte;
        struct {
            unsigned reserved : 7;
            unsigned success  : 1;
        } bits;
    } payload;
} disco_MESSAGE_ACK;

disco_MESSAGE message_packet(char* raw_message, encodings encoding, short retain, short duplicate);
disco_MESSAGE_ACK message_ack_packet(unsigned success, short duplicate);

#endif