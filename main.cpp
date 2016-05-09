#include <stdio.h>                                                                                            
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "component.h"
#include "log.h"

char * makeJson()
{
	cJSON * pJsonRoot = NULL;

	pJsonRoot = cJSON_CreateObject();
	if(NULL == pJsonRoot)
	{
		//error happend here
		return NULL;
	}
	cJSON_AddStringToObject(pJsonRoot, "hello", "hello world");
	cJSON_AddNumberToObject(pJsonRoot, "number", 10010);
	cJSON_AddBoolToObject(pJsonRoot, "bool", 1);
	cJSON * pSubJson = NULL;
	pSubJson = cJSON_CreateObject();
	if(NULL == pSubJson)
	{
		// create object faild, exit
		cJSON_Delete(pJsonRoot);
		return NULL;
	}
	cJSON_AddStringToObject(pSubJson, "subjsonobj", "a sub json string");
	cJSON_AddItemToObject(pJsonRoot, "subobj", pSubJson);

	char * p = cJSON_Print(pJsonRoot);
	// else use : 
	// char * p = cJSON_PrintUnformatted(pJsonRoot);
	if(NULL == p)
	{
		//convert json list to string faild, exit
		//because sub json pSubJson han been add to pJsonRoot, so just delete pJsonRoot, if you also delete pSubJson, it will coredump, and error is : double free
		cJSON_Delete(pJsonRoot);
		return NULL;
	}
	//free(p);

	cJSON_Delete(pJsonRoot);

	return p;
}

void parseJson(char * pMsg)
{
	if(NULL == pMsg)
	{
		return;
	}
	cJSON * pJson = cJSON_Parse(pMsg);
	if(NULL == pJson)                                                                                         
	{
		// parse faild, return
		return ;
	}

	// get string from json
	cJSON * pSub = cJSON_GetObjectItem(pJson, "hello");
	if(NULL == pSub)
	{
		//get object named "hello" faild
	}
	printf("obj_1 : %s\n", pSub->valuestring);

	// get number from json
	pSub = cJSON_GetObjectItem(pJson, "number");
	if(NULL == pSub)
	{
		//get number from json faild
	}
	printf("obj_2 : %d\n", pSub->valueint);

	// get bool from json
	pSub = cJSON_GetObjectItem(pJson, "bool");
	if(NULL == pSub)
	{
		// get bool from json faild
	}                                                                                                         
	printf("obj_3 : %d\n", pSub->valueint);

	// get sub object
	pSub = cJSON_GetObjectItem(pJson, "subobj");
	if(NULL == pSub)
	{
		// get sub object faild
	}
	cJSON * pSubSub = cJSON_GetObjectItem(pSub, "subjsonobj");
	if(NULL == pSubSub)
	{
		// get object from subject object faild
	}
	printf("sub_obj_1 : %s\n", pSubSub->valuestring);

	cJSON_Delete(pJson);
}

int main()
{
#if 0	
	char * p = makeJson();
	if(NULL == p)
	{
		return 0;
	}
	printf("%s\n", p);
	parseJson(p);                                                                                             
	free(p);
#endif
#if 1
	char szZigbeeComponentId[COMPONENT_ID_LEN_MAX] = "1";
	/*test Zigbee component interface*/
	cJSON *pComponentJsonRoot = NULL;

	pComponentJsonRoot = cJSON_CreateObject();
	if (NULL == pComponentJsonRoot)
	{
		PrintErrorLog("[ERROR]: <main> cJSON_CreateObject error!!!\n");
		return -1;
	}

	int iRet = 0;

	iRet = zigbee_register_component_request(pComponentJsonRoot, szZigbeeComponentId);
	
	char *p = cJSON_Print(pComponentJsonRoot);
	if(NULL == p)
	{
		//convert json list to string faild, exit
		//because sub json pSubJson han been add to pJsonRoot, so just delete pJsonRoot, if you also delete pSubJson, it will coredump, and error is : double free
		cJSON_Delete(pComponentJsonRoot);
		PrintErrorLog("[ERROR]: <main> cJSON_Delete error!!!");
		return -1;
	}

	cJSON_Delete(pComponentJsonRoot);
	PrintDebugLog("%s\n", p);
	//parseJson(p);                                                                                             
	free(p);

	{
		cJSON *pZigbeeComponentRet = cJSON_CreateObject();
		if (NULL == pZigbeeComponentRet)
		{
			PrintErrorLog("[ERROR]: cJSON_CreateObject pZigbeeComponentRet error!\n");
			return -1;
		}
		pZigbeeComponentRet = zigbee_register_component_request_success(szZigbeeComponentId);
		if (NULL != pZigbeeComponentRet)
		{
			p = cJSON_Print(pZigbeeComponentRet);
			PrintDebugLog("Success = \n%s\n", p);
		}

		memset(pZigbeeComponentRet, 0, sizeof(cJSON));
		char szErrorCode[COMPONENT_ERROR_CODE_LEN_MAX] = "00000000001";
		char szErrorMsg[COMPONENT_ERROR_MSG_LEN_MAX] = "register_component error";
		
		pZigbeeComponentRet = zigbee_register_component_request_fail(szZigbeeComponentId, szErrorCode, szErrorMsg);
		if (NULL != pZigbeeComponentRet)
		{
			p = cJSON_Print(pZigbeeComponentRet);
			PrintDebugLog("Fail = \n%s\n", p);
		}
		
		cJSON_Delete(pZigbeeComponentRet);
		free(p);
	}

	
#endif
	return 0;
}
