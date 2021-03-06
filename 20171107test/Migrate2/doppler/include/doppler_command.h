#ifndef DOPPLER_COMMAND
#define DOPPLER_COMMAND

enum COMMAND{
    CMD_NONE =  0 ,
    CMD_RESET_ALL  ,
    CMD_RESET_ENCODER  ,
    CMD_SET_CURRENT_GROUP ,
    CMD_GET_STATUS_INFO ,
    CMD_ADD_GROUP ,
    CMD_DEL_GROUP ,
    CMD_SET_ENCODER_TYPE,
    CMD_GET_CONFIG_SCAN ,
    CMD_SET_CONFIG_SCAN ,
    CMD_GET_CONFIG_FOCALLAW ,
    CMD_SET_CONFIG_FOCALLAW ,
    CMD_GET_CONFIG_PROBE ,
    CMD_SET_CONFIG_PROBE ,
    CMD_GET_CONFIG_WEDGE ,
    CMD_SET_CONFIG_WEDGE ,
    CMD_GET_CONFIG_PART  ,
    CMD_SET_CONFIG_PART  ,
    CMD_GET_CONFIG_UT_GENERAL ,
    CMD_SET_CONFIG_UT_GENERAL ,
    CMD_GET_CONFIG_UT_PULSER  ,
    CMD_SET_CONFIG_UT_PULSER  ,
    CMD_GET_CONFIG_UT_RECEIVER,
    CMD_SET_CONFIG_UT_RECEIVER,
    CMD_GET_CONFIG_UT_ADVANCED ,
    CMD_SET_CONFIG_UT_ADVANCED ,
    CMD_GET_CONFIG_GATE_INFO   ,
    CMD_SET_CONFIG_GATE_INFO   ,
    CMD_GET_CONFIG_DISPLAY_INFO  ,
    CMD_SET_CONFIG_DISPLAY_INFO  ,
    CMD_GET_GROUP_BEAMDELAY    ,
    CMD_SET_GROUP_BEAMDELAY    ,
    CMD_GET_GROUP_GAINOFFSET   ,
    CMD_SET_GROUP_GAINOFFSET   ,
    CMD_GET_SIZINGCURVE ,
    CMD_SET_SIZINGCURVE ,

    CMD_MAX_MAX_MAX  ,

    CMD_ENABLE_DATA_TRANSFER ,

    CMD_GET_VAL_GROUP_QTY ,
    CMD_GET_VAL_TOTAL_DATA_SIZE ,
    CMD_GET_VAL_GROUP_DATA_SIZE ,
    CMD_GET_VAL_GROUP_DATA_OFFSET ,
    CMD_GET_VAL_GROUP_BEAM_OFFSET ,
    CMD_GET_VAL_GROUP_BEAM_LENGTH ,

    CMD_GET_VAL_GAIN  ,
    CMD_SET_VAL_GAIN  ,

    CMD_GET_VAL_START ,
    CMD_SET_VAL_START ,

    CMD_GET_VAL_RANGE ,
    CMD_SET_VAL_RANGE ,


    CMD_GET_VAL_POINT_QTY ,
    CMD_SET_VAL_POINT_QTY ,

    CMD_GET_VAL_WEDGEDELAY ,
    CMD_SET_VAL_WEDGEDELAY ,

    CMD_GET_VAL_VELOCITY   ,
    CMD_SET_VAL_VELOCITY   ,

    CMD_GET_VAL_PRF   ,
    CMD_SET_VAL_PRF   ,
    CMD_EXIT_DISTANCE ,
};

enum ENCODER_TYPE{
    setup_ENCODER_TYPE_TIMER = 0,
    setup_ENCODER_TYPE_ENCODER_1,
    setup_ENCODER_TYPE_ENCODER_2,
};



#endif // DOPPLER_COMMAND

