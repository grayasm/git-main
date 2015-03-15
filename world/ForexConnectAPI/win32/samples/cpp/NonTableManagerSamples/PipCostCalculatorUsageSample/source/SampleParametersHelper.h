#pragma once

class SampleParametersHelper
{
public:

    /** Constructor.
    */
    SampleParametersHelper(const char *sampleName);

    /** Destructor.
    */
    virtual ~SampleParametersHelper();

    /** Addds the new parameter.
    */
    void addDescription(const char *fullKey, const char *shortKey, const char *description, bool optional = false);

    /** Prints the help information about the sample parameters.
    */
    void printHelp()const;

    /** Prints the information about the sample parameters values.
    */
    void printParamsValues()const;
  
    /** Parse the argument string and get the parameters values.
    */
    bool parse(int argc, char *argv[]);    

    /** Gets the parameter value by the parameter key(full key).
        Returns NULL, if no such parameter.
    */
    const char* getParamValue(const char *key) const;
    double getParamValueDouble(const char *key) const;
    int getParamValueInt(const char *key) const;

    /** Gets the last error description.
    */
    const char *getLastError() const;

    /** Gets the sample name.
    */
    const char *getSampleName() const;

private:    

    /** Description of the sample parameter.
    */
    class SampleParameter
    {
    public:

        /** Constructor.
        */
        SampleParameter(const char *fullKey, const char *shortKey, const char *description, bool optional = false);
        
        std::string mDescription;//!< Description of the parameter.
        bool mOptional; //!< Whether the parameter is optional.
        std::string mFullKey;//!< Full key used to specify parameter value in command line, e.g. "instrument"
        std::string mShortKey;//!< Short key sed to specify parameter value in command line, e.g. "i". Can be empty.

        std::string mValue;
    };

    const char *getArgument(int argc, char **argv, const char *key);

    typedef std::vector<SampleParameter*> TSampleParametersList;
    TSampleParametersList mDescriptions;
    std::string mSampleName;
    std::string mLastError;
};

