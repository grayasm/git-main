#pragma once

class SampleParams;
class LoginParams;
class SessionStatusListener;
class SampleParametersHelper;


class PipCostCalculatorUsageSample
{
public: 

    /** Constructor.
    */
    PipCostCalculatorUsageSample();
    
    /** Main method: executes the sample. 
        Returns whether the sample executed successfully.
    */
    bool execute(SampleParametersHelper &sampleParameters);   

    /** Gets the last error description or NULL if no error.
    */
    const char* getLastError() const;

private:

    /** Prints the pip costs.
    */
    void printPipCosts();

    /** Creates the session and login.
    */
    bool login(SampleParametersHelper &sampleParameters); 

    /** Disconnect.*/
    void logout();
  
    /** Sets the last error.
    */
    void setLastError(const char *error);
   
    IO2GSession *mSession;
    SessionStatusListener *mSessionListener;
    O2G2Ptr<IO2GTableManager> mTableManager;    
    std::string mLastError;

};


