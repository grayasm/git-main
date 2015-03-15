#include "stdafx.h"
#include <limits>
#include "SampleParametersHelper.h"

/** Constructor.
*/
SampleParametersHelper::SampleParameter::SampleParameter(const char *fullKey, const char *shortKey, const char *description, bool optional)
{    
    mDescription = description;
    mOptional = optional;
    mFullKey = fullKey;
    mShortKey = shortKey;
}


/** Constructor.
*/
SampleParametersHelper::SampleParametersHelper(const char *sampleName)
:mSampleName(sampleName)
{
}

/** Destructor.
*/
SampleParametersHelper::~SampleParametersHelper()
{
    for(TSampleParametersList::const_iterator it = mDescriptions.begin(); it != mDescriptions.end(); it++)
        delete *it;
}

/** Addds the new parameter.
*/
void SampleParametersHelper::addDescription(const char *fullKey, const char *shortKey, const char *description, bool optional)
{
    SampleParameter *paramDescr = new SampleParameter(fullKey, shortKey, description, optional);
    mDescriptions.push_back(paramDescr);
}

/** Gets the parameter value by the parameter key(full key).
Returns NULL, if no such parameter.
*/
const char* SampleParametersHelper::getParamValue(const char *key) const
{
    //TODO
    for(TSampleParametersList::const_iterator it = mDescriptions.begin(); it != mDescriptions.end(); it++)
    {
        SampleParameter *paramDescr = *it;
        if (paramDescr->mFullKey.compare(key) == 0)
            return paramDescr->mValue.c_str();
    }
    return NULL;
}

double SampleParametersHelper::getParamValueDouble(const char *key) const
{
    const char *val = getParamValue(key);
    if (val == NULL || *val == '\0')
        return std::numeric_limits<double>::quiet_NaN();    
     return atof(val);
}

int SampleParametersHelper::getParamValueInt(const char *key) const
{
    const char *val = getParamValue(key);
    if (val == NULL || *val == '\0')
        return std::numeric_limits<int>::quiet_NaN();    
     return atoi(val);
}

void SampleParametersHelper::printHelp()const
{
    std::cout << mSampleName << " sample parameters:" << std::endl << std::endl;
    for(TSampleParametersList::const_iterator it = mDescriptions.begin(); it != mDescriptions.end(); it++)
    {
        SampleParameter *paramDescr = *it;
        std::cout << '/' << paramDescr->mFullKey << " | --" << paramDescr->mFullKey;
        if (!paramDescr->mShortKey.empty())
            std::cout << " | /" << paramDescr->mShortKey << " | -" << paramDescr->mShortKey;
        std::cout << std::endl << paramDescr->mDescription;
        if (paramDescr->mOptional)
            std::cout << " Optional parameter.";
        std::cout << std::endl << std::endl;        
    }
}

/** Prints the information about the sample parameters values.
*/
void SampleParametersHelper::printParamsValues()const
{
    std::cout << "Running " << mSampleName << " with arguments:" << std::endl;    
    for(TSampleParametersList::const_iterator it = mDescriptions.begin(); it != mDescriptions.end(); it++)
    {
        SampleParameter *paramDescr = *it;
        if (paramDescr->mFullKey.compare("password") == 0)
            continue;
        if (!paramDescr->mValue.empty())
            std::cout << paramDescr->mFullKey << "=\"" << paramDescr->mValue << "\"; ";
    }
    std::cout << std::endl;
}

bool SampleParametersHelper::parse(int argc, char *argv[])
{
    for(TSampleParametersList::iterator it = mDescriptions.begin(); it != mDescriptions.end(); it++)
    {
        SampleParameter *param = *it;
        //try to load using short key        
        if (!param->mShortKey.empty())
            param->mValue = getArgument(argc, argv, param->mShortKey.c_str());
        //if not loaded, try to load using the full key
        if (param->mValue.empty())
            param->mValue = getArgument(argc, argv, param->mFullKey.c_str()); 
        if (param->mValue.empty() && !param->mOptional)
        {
            char bufError[500];
            if (!param->mShortKey.empty())
                _snprintf_s(bufError, 500, 500, "%s is not specified (/%s|-%s|/%s|--%s)", param->mFullKey.c_str(), param->mShortKey.c_str(), param->mShortKey.c_str(), param->mFullKey.c_str(), param->mFullKey.c_str());
            else
                _snprintf_s(bufError, 500, 500, "%s is not specified (/%s|--%s)", param->mFullKey.c_str(), param->mFullKey.c_str(), param->mFullKey.c_str());
            mLastError = bufError;
            return false;
        }
    }
    return true;
}

const char *SampleParametersHelper::getArgument(int argc, char **argv, const char *key)
{
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i][0] == '-' || argv[i][0] == '/')
        {
            int iDelimOffset = 0;
            if (strncmp(argv[i], "--", 2) == 0)
                iDelimOffset = 2;
            else if (strncmp(argv[i], "-", 1) == 0 || strncmp(argv[i], "/", 1) == 0)
                iDelimOffset = 1;

            if (_stricmp(argv[i] + iDelimOffset, key) == 0 && argc > i+1)
                return argv[i+1];
        }
    }
    return "";
}

/** Gets the last error description.
*/
const char *SampleParametersHelper::getLastError() const
{
    return mLastError.c_str();
}

/** Gets the sample name.
*/
const char *SampleParametersHelper::getSampleName() const
{
    return mSampleName.c_str();
}