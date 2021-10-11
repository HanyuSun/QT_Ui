/**
 *!
 * \file        b_protocol.c
 * \version     v0.1.0
 * \date        2020/03/15
 * \author      Bean(notrynohigh@outlook.com)
 *******************************************************************************
 * @attention
 * 
 * Copyright (c) 2020 Bean
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************
 */
   
/*Includes ----------------------------------------------*/
#include "b_protocol.h"
#include <stdint.h>
#if 1
#include <string.h>
/** 
 * \addtogroup BABYOS
 * \{
 */

/** 
 * \addtogroup PROTOCOL
 * \{
 */


/** 
 * \defgroup PROTOCOL_Private_TypesDefinitions
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Private_Defines
 * \{
 */
//<o> Secret Key 1
#define _SECRET_KEY1                1
//<o> Secret Key 2
#define _SECRET_KEY2                22
//<o> Secret Key 3
#define _SECRET_KEY3                333
//<o> Secret Key 4
#define _SECRET_KEY4                4444
/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Private_Macros
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Private_Variables
 * \{
 */

static bProtocolInfo_t  bProtocolInfo[1];
static uint8_t bProtocolInfoIndex = 0;

#define _PROTO_TEA_DELTA                  0x9e3779b9
const static uint32_t Keys[4] = {_SECRET_KEY1, _SECRET_KEY2, _SECRET_KEY3, _SECRET_KEY4};

/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Private_FunctionPrototypes
 * \{
 */
   
/**
 * \}
 */
   
/** 
 * \defgroup PROTOCOL_Private_Functions
 * \{
 */
static uint8_t _bProtocolCalCheck(uint8_t *pbuf, bProtoLen_t len)
{
    uint8_t tmp;
    bProtoLen_t i;
    tmp = pbuf[0];
    for(i = 1;i < len;i++)
    {
        tmp += pbuf[i];
    }
    return tmp;
} 

static void _bProtocolEncryptGroup(uint32_t *text, uint32_t *key)
{
    uint32_t sum = 0, v0 = text[0], v1 = text[1];
    uint32_t k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
    int i = 0;

    for(i = 0;i < 16;i++)
    {
        sum += _PROTO_TEA_DELTA;
        v0 += (v1 << 4) + k0 ^ v1 + sum ^ (v1 >> 5) + k1;
        v1 += (v0 << 4) + k2 ^ v0 + sum ^ (v0 >> 5) + k3;
    }
    text[0] = v0;
    text[1] = v1;
}

static void _bProtocolDecryptGroup(uint32_t *text, uint32_t *key)
{
    uint32_t sum = _PROTO_TEA_DELTA * 16, v0 = text[0], v1 = text[1];
    uint32_t k0 = key[0], k1 = key[1], k2 = key[2], k3 = key[3];
    int i = 0;

    for(i = 0;i < 16;i++)
    {
        v1 -= (v0 << 4) + k2 ^ v0 + sum ^ (v0 >> 5) + k3;
        v0 -= (v1 << 4) + k0 ^ v1 + sum ^ (v1 >> 5) + k1;
        sum -= _PROTO_TEA_DELTA;
    }
    text[0] = v0;
    text[1] = v1;
}


/**
 * \}
 */
   
/** 
 * \addtogroup PROTOCOL_Exported_Functions
 * \{
 */

/**
 * \brief Create a protocol instance
 * \param id system id
 * \param f Dispatch Function \ref pdispatch
 * \retval Instance ID
 *          \arg >=0  valid
 *          \arg -1   invalid
 */
int bProtocolRegist(bProtoID_t id, pdispatch f)
{
    if(bProtocolInfoIndex >= 1 || f == NULL)
    {
        return -1;
    }
    bProtocolInfo[bProtocolInfoIndex].id = id;
    bProtocolInfo[bProtocolInfoIndex].f = f;
    bProtocolInfoIndex += 1;
    return (bProtocolInfoIndex - 1);
}


/**
 * \brief Check ID and call dispatch function
 * \param no Protocol instance \ref bProtocolRegist
 * \param pbuf Pointer to data buffer
 * \param len Amount of data
 * \retval Result
 *          \arg 0  OK
 *          \arg -1 ERR
 */
int bProtocolParse(int no, uint8_t *pbuf, bProtoLen_t len)
{
    bProtocolHead_t *phead = (bProtocolHead_t *)pbuf;
    int length;
    uint8_t crc;
    if(pbuf == NULL || len < (sizeof(bProtocolHead_t) + 1) || no >= bProtocolInfoIndex || no < 0)
    {
        return -1;
    }
    
    if(phead->head != PROTOCOL_HEAD)
    {
        return -1;
    }
    
    length = phead->len + sizeof(bProtocolHead_t);
    if(length > len)
    {
        return -1;
    }  
    crc = _bProtocolCalCheck(pbuf, length - 1);
    if(crc != pbuf[length - 1])
    {
        //b_log_e("crc error!%d %d", crc, pbuf[length - 1]);
        return -1;
    }
    return bProtocolInfo[no].f(phead->device_id, phead->cmd, &pbuf[sizeof(bProtocolHead_t)], phead->len - 1);
}



/**
 * \brief Call this function after system ID is changed
 * \param no Protocol instance \ref bProtocolRegist
 * \param id System ID
 * \retval Result
 *          \arg 0  OK
 *          \arg -1 ERR
 */
int bProtocolSetID(int no, bProtoID_t id)
{
    if(no >= bProtocolInfoIndex || no < 0)
    {
        return -1;
    }
    bProtocolInfo[no].id = id;
    return 0;
}



/**
 * \brief pack and start a TX request
 * \param no Protocol instance \ref bProtocolRegist
 * \param id ID of the target
 * \param cmd Protocol command
 * \param param Pointer to the command param
 * \param param_size size of the param
 * \param pbuf Pointer to the buffer that save the packed data
 * \retval Result
 *          \arg >0 Amount of data in the pbuf
 *          \arg -1 ERR
 */
int bProtocolPack(int no, bProtoID_t id, uint8_t cmd, uint8_t *param, bProtoLen_t param_size, uint8_t *pbuf)
{
    int length = 0;
    bProtocolHead_t *phead;

    if((param == NULL && param_size > 0) || no >= bProtocolInfoIndex || no < 0 || pbuf == NULL)
    {
        return -1;
    }
    phead = (bProtocolHead_t *)pbuf;
    phead->head = PROTOCOL_HEAD;
    phead->device_id = id;
    phead->cmd = cmd;
    phead->len = param_size+1;
    memcpy(&pbuf[sizeof(bProtocolHead_t)], param, param_size);
    length = sizeof(bProtocolHead_t) + phead->len;
    pbuf[length - 1] = _bProtocolCalCheck(pbuf, length - 1);
    return length;
}



void _bProtocolEncrypt(uint8_t *text, uint32_t size)
{
    uint32_t number = size >> 3;
    int i = 0;

    if(size < 8)
    {
        return;
    }
    for(i = 0;i < number;i++)
    {
        _bProtocolEncryptGroup(&(((uint32_t *)text)[i * 2]), (uint32_t *)Keys);
    }
}


void _bProtocolDecrypt(uint8_t *text, uint32_t size)
{
    uint32_t number = size >> 3;
    int  i = 0;

    if(size < 8)
    {
        return;
    }

    for(i = 0;i < number;i++)
    {
        _bProtocolDecryptGroup(&(((uint32_t *)text)[i * 2]), (uint32_t *)Keys);
    }
}

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */
#endif

/************************ Copyright (c) 2019 Bean *****END OF FILE****/

