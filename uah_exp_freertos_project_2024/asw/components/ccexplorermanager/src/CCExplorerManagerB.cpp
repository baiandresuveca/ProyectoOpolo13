#include <public/ccexplorermanager_iface_v1.h>

// ***********************************************************************

// class EDROOM_CTX_Top_0

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCExplorerManager::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(CCExplorerManager &act,
	 CDEventList & EDROOMpVarVCurrentEvList,
	 CDTCHandler & EDROOMpVarVCurrentTC,
	 CDTMList & EDROOMpVarVCurrentTMList,
	 CEDROOMPOOLCDTMList & EDROOMpPoolCDTMList,
	 CEDROOMPOOLCDTCHandler & EDROOMpPoolCDTCHandler ):

	EDROOMcomponent(act),
	Msg(EDROOMcomponent.Msg),
	MsgBack(EDROOMcomponent.MsgBack),
	GuidanceCtrl(EDROOMcomponent.GuidanceCtrl),
	BKGExecCtrl(EDROOMcomponent.BKGExecCtrl),
	HK_FDIRCtrl(EDROOMcomponent.HK_FDIRCtrl),
	TMChannelCtrl(EDROOMcomponent.TMChannelCtrl),
	EvActionQueue(EDROOMcomponent.EvActionQueue),
	RxTC(EDROOMcomponent.RxTC),
	VCurrentEvList(EDROOMpVarVCurrentEvList),
	VCurrentTC(EDROOMpVarVCurrentTC),
	VCurrentTMList(EDROOMpVarVCurrentTMList),
	EDROOMPoolCDTMList(EDROOMpPoolCDTMList),
	EDROOMPoolCDTCHandler(EDROOMpPoolCDTCHandler)
{
}

CCExplorerManager::EDROOM_CTX_Top_0::EDROOM_CTX_Top_0(EDROOM_CTX_Top_0 &context):

	EDROOMcomponent(context.EDROOMcomponent),
	Msg(context.Msg),
	MsgBack(context.MsgBack),
	GuidanceCtrl(context.GuidanceCtrl),
	BKGExecCtrl(context.BKGExecCtrl),
	HK_FDIRCtrl(context.HK_FDIRCtrl),
	TMChannelCtrl(context.TMChannelCtrl),
	EvActionQueue(context.EvActionQueue),
	RxTC(context.RxTC),
	VCurrentEvList(context.VCurrentEvList),
	VCurrentTC(context.VCurrentTC),
	VCurrentTMList(context.VCurrentTMList),
	EDROOMPoolCDTMList(context.EDROOMPoolCDTMList ),
	EDROOMPoolCDTCHandler(context.EDROOMPoolCDTCHandler )
{

}

	// EDROOMSearchContextTrans********************************************

bool CCExplorerManager::EDROOM_CTX_Top_0::EDROOMSearchContextTrans(
			TEDROOMTransId &edroomCurrentTrans)
			{

	bool edroomValidMsg=false; 

	 switch(Msg->signal)
	{

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User-defined Functions   ****************************

void	CCExplorerManager::EDROOM_CTX_Top_0::FExecPrioTC()

{

 PUSPrioTCExecutor::ExecTC(VCurrentTC,VCurrentTMList,VCurrentEvList);

}



void	CCExplorerManager::EDROOM_CTX_Top_0::FFwdGuidanceTC()

{
   //Allocate data from pool
  CDTCHandler * pSGuidanceTC_Data = EDROOMPoolCDTCHandler.AllocData();
	
		// Complete Data 
	
	*pSGuidanceTC_Data=VCurrentTC;
   //Send message 
   GuidanceCtrl.send(SGuidanceTC,pSGuidanceTC_Data,&EDROOMPoolCDTCHandler); 
}



void	CCExplorerManager::EDROOM_CTX_Top_0::FFwdHK_FDIRTC()

{
   //Allocate data from pool
  CDTCHandler * pSHK_FDIR_TC_Data = EDROOMPoolCDTCHandler.AllocData();
	
		// Complete Data 
	
*pSHK_FDIR_TC_Data=VCurrentTC;   
   //Send message 
   HK_FDIRCtrl.send(SHK_FDIR_TC,pSHK_FDIR_TC_Data,&EDROOMPoolCDTCHandler); 
}



void	CCExplorerManager::EDROOM_CTX_Top_0::FFwdToBKGTCExec()

{
   //Allocate data from pool
  CDTCHandler * pSBKGTC_Data = EDROOMPoolCDTCHandler.AllocData();
	
		// Complete Data 
	
	*pSBKGTC_Data=VCurrentTC;  
   //Send message 
   BKGExecCtrl.send(SBKGTC,pSBKGTC_Data,&EDROOMPoolCDTCHandler); 
}



void	CCExplorerManager::EDROOM_CTX_Top_0::FGetEvAction()

{
   //Handle Msg->data
  CDEvAction & varEDROOMIRQsignal = *(CDEvAction *)Msg->data;
	
	
PUSService19::GetEvActionTCHandler(varEDROOMIRQsignal,VCurrentTC);
 
 
 

}



void	CCExplorerManager::EDROOM_CTX_Top_0::FGetTC()

{
   //Handle Msg->data
  CDTCHandler & varEDROOMIRQsignal = *(CDTCHandler *)Msg->data;
	
		// Data access
	
VCurrentTC=varEDROOMIRQsignal;
 
PUSService1::TryTCAcceptation(VCurrentTC);

}



void	CCExplorerManager::EDROOM_CTX_Top_0::FInit()

{

RxTC.MaskIRQ();
 
RxTC.InstallHandler();
SC_Channel_Init(&RxTC);
 
RxTC.UnMaskIRQ();

}



void	CCExplorerManager::EDROOM_CTX_Top_0::FInvokeTxTMList()

{
   //Allocate data from pool
  CDTMList * pSTxTM_Data = EDROOMPoolCDTMList.AllocData();
	
		// Complete Data 
	
	*pSTxTM_Data=VCurrentTMList;    
	VCurrentTMList.Clear();
   //Invoke synchronous communication 
   MsgBack=TMChannelCtrl.invoke(STxTM,pSTxTM_Data,&EDROOMPoolCDTMList); 
}



void	CCExplorerManager::EDROOM_CTX_Top_0::FMngTCAcceptation()

{

 
PUSService1::BuildTM_1_1(VCurrentTC, VCurrentTMList);

}



void	CCExplorerManager::EDROOM_CTX_Top_0::FMngTCRejection()

{

 
PUSService1::BuildTM_1_2(VCurrentTC, VCurrentTMList);
 
PUSService1::CompleteTCRejection(VCurrentTC);

}



void	CCExplorerManager::EDROOM_CTX_Top_0::FReboot()

{

PUSService128::MngReboot();

}



bool	CCExplorerManager::EDROOM_CTX_Top_0::GAcceptTC()

{

return VCurrentTC.IsAccepted();

}



bool	CCExplorerManager::EDROOM_CTX_Top_0::GFwdToBKGTCExec()

{

 return VCurrentTC.IsBKGTC();

}



bool	CCExplorerManager::EDROOM_CTX_Top_0::GFwdToGuidanceTC()

{

return VCurrentTC.IsGuidanceTC();

}



bool	CCExplorerManager::EDROOM_CTX_Top_0::GFwdToHK_FDIR()

{

return VCurrentTC.IsHK_FDIRTC();

}



bool	CCExplorerManager::EDROOM_CTX_Top_0::GFwToGuidance()

{

return VCurrentTC.IsGuidanceTC();

}



bool	CCExplorerManager::EDROOM_CTX_Top_0::GToReboot()

{

return VCurrentTC.IsRebootTC();

}



	//********************************** Pools *************************************

	//CEDROOMPOOLCDTMList

CCExplorerManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::CEDROOMPOOLCDTMList(
			TEDROOMUInt32 elemCount,CDTMList* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDTMList))
{
}

CDTMList *	CCExplorerManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTMList::AllocData()
{
	return(CDTMList*)CEDROOMProtectedMemoryPool::AllocData();
}

	//CEDROOMPOOLCDTCHandler

CCExplorerManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTCHandler::CEDROOMPOOLCDTCHandler(
			TEDROOMUInt32 elemCount,CDTCHandler* pMem,bool * pMemMarks):
				CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks,
					sizeof(CDTCHandler))
{
}

CDTCHandler *	CCExplorerManager::EDROOM_CTX_Top_0::CEDROOMPOOLCDTCHandler::AllocData()
{
	return(CDTCHandler*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOM_SUB_Top_0

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCExplorerManager::EDROOM_SUB_Top_0::EDROOM_SUB_Top_0 (CCExplorerManager&act
	,CEDROOMMemory *pEDROOMMemory):
		EDROOM_CTX_Top_0(act,
			VCurrentEvList,
			VCurrentTC,
			VCurrentTMList,
			EDROOMPoolCDTMList,
			EDROOMPoolCDTCHandler),
		EDROOMPoolCDTMList(
			10, pEDROOMMemory->poolCDTMList,
			pEDROOMMemory->poolMarkCDTMList),
		EDROOMPoolCDTCHandler(
			10, pEDROOMMemory->poolCDTCHandler,
			pEDROOMMemory->poolMarkCDTCHandler)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCExplorerManager::EDROOM_SUB_Top_0::EDROOMBehaviour()
{

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIArrival();

	do
	{

		//Take next transition

		switch(edroomCurrentTrans.localId)
		{

			//Next Transition is Init
			case (Init):
				//Execute Action 
				FInit();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point NewRxTC
			case (NewRxTC):

				//Msg->Data Handling 
				FGetTC();
				//Evaluate Branch Accepted
				if( GAcceptTC() )
				{
					//Execute Action 
					FMngTCAcceptation();
					//Invoke Synchronous Message 
					FInvokeTxTMList();

					//Branch taken is NewRxTC_Accepted
					edroomCurrentTrans.localId =
						NewRxTC_Accepted;

					//Next State is ValidTC
					edroomNextState = ValidTC;
				 } 
				//Default Branch NotAccepted
				else
				{
					//Execute Action 
					FMngTCRejection();
					//Invoke Synchronous Message 
					FInvokeTxTMList();

					//Branch taken is NewRxTC_NotAccepted
					edroomCurrentTrans.localId =
						NewRxTC_NotAccepted;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				break;
			//Next Transition is NewEvAction
			case (NewEvAction):
				//Msg->Data Handling 
				FGetEvAction();
				//Next State is ValidTC
				edroomNextState = ValidTC;
				break;
			//To Choice Point HandleTC
			case (HandleTC):

				//Evaluate Branch ToReboot
				if( GToReboot() )
				{
					//Execute Action 
					FExecPrioTC();
					//Invoke Synchronous Message 
					FInvokeTxTMList();

					//Branch taken is HandleTC_ToReboot
					edroomCurrentTrans.localId =
						HandleTC_ToReboot;

					//Next State is Reboot
					edroomNextState = Reboot;
				 } 
				//Evaluate Branch FwdHK_FDIRTC
				else if( GFwdToHK_FDIR() )
				{
					//Send Asynchronous Message 
					FFwdHK_FDIRTC();

					//Branch taken is HandleTC_FwdHK_FDIRTC
					edroomCurrentTrans.localId =
						HandleTC_FwdHK_FDIRTC;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch FwdToBKGTCExec
				else if( GFwdToBKGTCExec() )
				{
					//Send Asynchronous Message 
					FFwdToBKGTCExec();

					//Branch taken is HandleTC_FwdToBKGTCExec
					edroomCurrentTrans.localId =
						HandleTC_FwdToBKGTCExec;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch FwdToGuidanceTC
				else if( GFwdToGuidanceTC() )
				{
					//Send Asynchronous Message 
					FFwdGuidanceTC();

					//Branch taken is HandleTC_FwdToGuidanceTC
					edroomCurrentTrans.localId =
						HandleTC_FwdToGuidanceTC;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Default Branch ExecPrioTC
				else
				{
					//Execute Action 
					FExecPrioTC();
					//Invoke Synchronous Message 
					FInvokeTxTMList();

					//Branch taken is HandleTC_ExecPrioTC
					edroomCurrentTrans.localId =
						HandleTC_ExecPrioTC;

					//Next State is Ready
					edroomNextState = Ready;
				 } 
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState)
		{

				//Go to the state I
			case (I):
				//Arrival to state I
				edroomCurrentTrans=EDROOMIArrival();
				break;

				//Go to the state Ready
			case (Ready):
				//Arrival to state Ready
				edroomCurrentTrans=EDROOMReadyArrival();
				break;

				//Go to the state Reboot
			case (Reboot):
				//Execute Entry Action 
				FReboot();
				//Arrival to state Reboot
				edroomCurrentTrans=EDROOMRebootArrival();
				break;

				//Go to the join point ValidTC
			case (ValidTC):
				//Arrival to join point ValidTC
				edroomCurrentTrans=EDROOMValidTCArrival();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Context Init**********************************************

void CCExplorerManager::EDROOM_SUB_Top_0::EDROOMInit()
{

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCExplorerManager::EDROOM_SUB_Top_0::EDROOMIArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



//	 ***********************************************************************

//	 JoinPoint ValidTC

//	 ***********************************************************************



TEDROOMTransId CCExplorerManager::EDROOM_SUB_Top_0::EDROOMValidTCArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  HandleTC
	edroomCurrentTrans.localId = HandleTC;
	edroomCurrentTrans.distanceToContext = 0 ;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCExplorerManager::EDROOM_SUB_Top_0::EDROOMReadyArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		switch(Msg->signal)
		{

			case (EDROOMIRQsignal): 

				 if (*Msg->GetPInterface() == RxTC)
				{

					//Next transition is  NewRxTC
					edroomCurrentTrans.localId = NewRxTC;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				 else if (*Msg->GetPInterface() == EvActionQueue)
				{

					//Next transition is  NewEvAction
					edroomCurrentTrans.localId= NewEvAction;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Reboot

	// ***********************************************************************



TEDROOMTransId CCExplorerManager::EDROOM_SUB_Top_0::EDROOMRebootArrival()
{

	TEDROOMTransId edroomCurrentTrans;

	bool edroomValidMsg=false;

	do
	{

		EDROOMNewMessage ();

		if (false == edroomValidMsg)
		{
			 edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

		}

	} while (false == edroomValidMsg);

	return(edroomCurrentTrans);

}



