#pragma once

class Order2Go2 CO2GHtmlContentUtils
{
 public:
     /** Converts relative paths specified as tag parameters to absolute paths.
         Replaces the paths for params ("href" and "src") with tags ("link", "a", "img").
     */
     static std::string replaceRelativePathWithAbsolute(const char *sHtmlContent, const char *cszAbsPathPrefix);
};

