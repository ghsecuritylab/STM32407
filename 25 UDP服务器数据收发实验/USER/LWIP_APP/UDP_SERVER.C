/*********************************************************************************
**********************MCU启明 STM32F407应用开发板(高配版)*************************
**********************************************************************************
* 文件名称: UDP_SERVER.C                                                        *
* 文件简述：UDP服务器运用                                                        *
* 创建日期：2015.10.08                                                           *
* 版    本：V1.0                                                                 *
* 作    者：Clever                                                               *
* 说    明：                                                                     * 
**********************************************************************************
*********************************************************************************/
#include "stm32f4x7_eth.h"
#include "stm32f4x7_eth_bsp.h"
#include "netconf.h"
#include "tcp.h"
#include "udp.h"
#include "string.h"

#include "UDP_SERVER.h"


/****************************************************************************
* 名    称: udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
* 功    能：udp数据接收和发送
* 入口参数： 
* 返回参数： 
* 说    明：这是一个回调函数，当一个udp段到达这个连接时会被调�       
****************************************************************************/
udp_server_recv(void *arg, struct udp_pcb *pcb, struct pbuf *p,struct ip_addr *addr, u16_t port)
{
	struct ip_addr destAddr = *addr;  // 获取远程主机 IP地址  
	struct pbuf *p_temp = p;
	//while(p_temp != NULL)
//	{
		udp_sendto(pcb,p_temp,&destAddr,port); // 将收到的数据再发送出去  
		p_temp = p_temp->next;
//	}
	pbuf_free(p); 						// 释放该UDP段  
}

/****************************************************************************
* 名    称：UDP_server_init(void))
* 功    能：完成UDP服务器的初始化，主要是使得UDP通讯快进入监听状态
* 入口参数： 
* 返回参数： 
* 说    明：     
****************************************************************************/
void UDP_server_init(void)
{
	struct udp_pcb *pcb;
	pcb = udp_new();							            	// 申请udp控制块
	udp_bind(pcb,IP_ADDR_ANY,UDP_LOCAL_PORT);   // 绑定本地IP地址和端口号（作为udp服务器） 
	udp_recv(pcb,udp_server_recv,NULL); 			  // 设置UDP段到时的回调函数 */
}


