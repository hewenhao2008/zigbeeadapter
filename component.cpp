#include <stdio.h>
#include "common.h"
#include "cJSON.h"
#include "component.h"

int zigbee_register_component_request(cJSON *pComponentJsonRoot, char *szId)
{
	if (NULL == pComponentJsonRoot || NULL == szId)
	{
		printf("[ERROR]: <zigbee_register_component> pComponentJsonRoot is NULL!!!\n");
		return -1;
	}	
	/*jsonrp*/
	cJSON_AddStringToObject(pComponentJsonRoot, JSONRPC_KEY_NAME, JSONRPC_KEY_VALUE);
	/*method*/
	cJSON_AddStringToObject(pComponentJsonRoot, "method", "register_component");
	/*params*/
	cJSON * pSubJsonParams = NULL;
	pSubJsonParams = cJSON_CreateObject();
	if(NULL == pSubJsonParams)
	{
		// create object faild, exit
		printf("[ERROR]: <cJSON_CreateObject> error!!!\n");
		cJSON_Delete(pComponentJsonRoot);
		return -1;
	}
	cJSON_AddStringToObject(pSubJsonParams, "name", "zigbee_link_adapter");
	cJSON_AddStringToObject(pSubJsonParams, "type", "link_adapter:zigbee_link_adapter");
	cJSON_AddItemToObject(pComponentJsonRoot, "params", pSubJsonParams);

	/*id*/
	cJSON_AddStringToObject(pComponentJsonRoot, "id", szId);
	
	return 0;	
}

cJSON *zigbee_register_component_request_success(char *szId)
{	
	if (NULL == szId)
	{
		printf("[ERROR]: <zigbee_register_component_request_success> szId is NULL!!!\n");
		return NULL;
	}	
	
	cJSON *pComponentJsonSuccess = cJSON_CreateObject();
	if (NULL == pComponentJsonSuccess)
	{
		printf("[ERROR]: <zigbee_register_component_request_success> cJSON_CreateObject error!\n");
		return NULL;
	}

	cJSON_AddStringToObject(pComponentJsonSuccess, JSONRPC_KEY_NAME, JSONRPC_KEY_VALUE);
	cJSON_AddStringToObject(pComponentJsonSuccess, "result", "success");
	cJSON_AddStringToObject(pComponentJsonSuccess, "id", szId);	

	return pComponentJsonSuccess;
}

cJSON *zigbee_register_component_request_fail(char *szId, char *szErrorCode, char *szErrorMsg)
{	
	if (NULL == szId || NULL == szErrorCode || NULL == szErrorMsg)
	{
		printf("[ERROR]: zigbee_register_component_request_fail error!\n");
		return NULL;
	}
	cJSON *pComponentJsonFail = cJSON_CreateObject();
	if (NULL == pComponentJsonFail)
	{
		printf("[ERROR]: <zigbee_register_component_request_fail> cJSON_CreateObject pComponentJsonFail error!\n");
		return NULL;
	}
	
	cJSON_AddStringToObject(pComponentJsonFail, JSONRPC_KEY_NAME, JSONRPC_KEY_VALUE);

	cJSON * pSubJsonError = cJSON_CreateObject();
	if (NULL == pSubJsonError)
	{
		printf("[ERROR]: <zigbee_register_component_request_fail> cJSON_CreateObject pSubJsonError error!\n");		
		cJSON_Delete(pComponentJsonFail);
		return NULL;
	}
	cJSON_AddStringToObject(pSubJsonError, "code", szErrorCode);
	cJSON_AddStringToObject(pSubJsonError, "message", szErrorMsg);
	cJSON_AddItemToObject(pComponentJsonFail, "error", pSubJsonError);
	
	cJSON_AddStringToObject(pComponentJsonFail, "id", szId);

	return pComponentJsonFail;
}

