
#include "ModeControl.h"
#include "Input.h"
#include "ThreeAxisController.h"
#include "Inputproceed.h"
#include "LimitControllerInput.h"
#include "TMProcess.h"
#include "FaultJudgeProceed.h"
#include "TcProcess.h"
#include "PeriodControl.h"

/*@ 
requires \valid(pIp);
assigns pIp->flgGryoCalc, pIp->countSate, pIp->flg160INT;
ensures \valid(pIp); // Ensures that pIp remains valid after execution
*/
void PeriodControlFun(PeriodControl *pIp)
{
    do
    {
        IPCREATE(TcProcess, ipTcProcess);
        IPCALL(ipTcProcess);

        IPCREATE(Input, ipInput);
        IPCALL(ipInput);

        IPCREATE(Inputproceed, ipInputproceed);
        IPCALL(ipInputproceed);

        IPCREATE(ModeControl, ipModeControl);
        IPCALL(ipModeControl);

        IPCREATE(LimitControllerInput, ipLimitControllerInput);
        IPCALL(ipLimitControllerInput);

        IPCREATE(ThreeAxisController, ipThreeAxisController);
        IPCALL(ipThreeAxisController);

        IPCREATE(FaultJudgeProceed, ipFaultJudgeProceed);
        IPCALL(ipFaultJudgeProceed);

        pIp->flgGryoCalc = FALSE;

        pIp->countSate++;

        /*@ 
        requires pIp->countSate <= 0xFFFFFFF0;
        ensures pIp->countSate == 4000 || pIp->countSate <= 0xFFFFFFF0;
        assigns pIp->countSate;
        */
        if (pIp->countSate > 0xFFFFFFF0)
        {
            pIp->countSate = 4000;
        }

        IPCREATE(TMProcess, ipTMProcess);
        IPCALL(ipTMProcess);

        /*@ loop invariant pIp->flg160INT != 0xCCCC;
            loop assigns pIp->flg160INT;
            loop variant pIp->flg160INT; // Assuming flg160INT decreases or remains constant
        */
        while (pIp->flg160INT != 0xCCCC)
        {
            ;
        }

        pIp->flg160INT = 0x3333;

    } while (1);

    return;
}
