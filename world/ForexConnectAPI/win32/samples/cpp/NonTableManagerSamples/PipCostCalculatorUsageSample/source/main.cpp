#include "stdafx.h"
#include "SampleParametersHelper.h"
#include "PipCostCalculatorUsageSample.h"

/** Helper method. Fills list of the parameters descriptions used in the smple.
*/
void init(SampleParametersHelper &parametersHelper);

int main(int argc, char *argv[])
{
    //fill list of the parameters descriptions used in the sample
    SampleParametersHelper parametersHelper("PipCostCalculatorUsageSample");
    init(parametersHelper);
    
    //process the input parameters
    if (argc == 1)//if no input parameters - print help
    {
        parametersHelper.printHelp();        
        return -1;
    }
    if (!parametersHelper.parse(argc, argv))
    {
        std::cout<<parametersHelper.getLastError()<<std::endl;
        return -1;
    }

    parametersHelper.printParamsValues(); 
   
    bool bWasError = false;
    PipCostCalculatorUsageSample sample;
    if (!sample.execute(parametersHelper))
    {
        std::cout << "Failed." << sample.getLastError() <<std::endl;
        bWasError = true;      
    }

    return bWasError ? -1 : 0;
}

/** Helper method. Creates list of the parameters descriptions used in the smple.
*/
void init(SampleParametersHelper &parametersHelper)
{
    //login parameters
    parametersHelper.addDescription("login", "l", "Your user name.");
    parametersHelper.addDescription("password", "p", "Your password.");
    parametersHelper.addDescription("url", "u", "The server URL. For example, http://www.fxcorporate.com/Hosts.jsp.");
    parametersHelper.addDescription("connection", "c", "The connection name. For example, \"Demo\" or \"Real\".");
    parametersHelper.addDescription("sessionid", "", "The database name. Required only for users who have accounts in more than one database.", true);
    parametersHelper.addDescription("pin", "", "Your pin code. Required only for users who have a pin.", true);    
}

