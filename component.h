#ifndef __COMPONENT_H
#define __COMPONENT_H

#ifdef __cplusplus
extern "C"
{
#endif

#define COMPONENT_ID_LEN_MAX			8
#define COMPONENT_ERROR_CODE_LEN_MAX	16
#define COMPONENT_ERROR_MSG_LEN_MAX		128

int zigbee_register_component_request(cJSON *pComponentJsonRoot, char *szId);
cJSON *zigbee_register_component_request_success(char *szId);
cJSON *zigbee_register_component_request_fail(char *szId, char *szErrorCode, char *szErrorMsg);

#ifdef __cplusplus
}
#endif

#endif

