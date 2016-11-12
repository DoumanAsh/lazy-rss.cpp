#pragma once

#include <vector>
#include <string>
#include <exception>

namespace cli {

/**
 * Command line parse error.
 */
class ParseError: public std::exception {
    public:
        /** Initializes empty @ref ParseError without error. */
        ParseError();

        /**
         * Initializes @ref ParseError with result and default error desciption.
         *
         * Default error description is "Illegal argument"
         */
        explicit ParseError(int result);

        /**
         * Initializes @ref ParseError with result and desciption.
         */
        explicit ParseError(int result, const char* desciption);

        /**
         * Returns reason
         *
         * It is empty string on no-error case.
         */
        virtual const char* what() const throw();

        /**
         * Returns return code.
         *
         * 0 is passed upon requiring to print help.
         */
        int result() const;

    private:
        int _result;
        const char* _desc;
};

/**
 * Command line options parser.
 */
class Options {
    public:
        /**
         * Constructor.
         *
         * @param argc The `argc` parameter of main() function.
         * @param argv The `argv` parameter of main() function.
         */
        Options(int argc, char *argv[]);

        /** Return array of urls to parse. */
        const std::vector<std::string>& urls() const;

        /**
         * Getter of usage.
         */
        static const char* usage;

    private:
        void _handle_option(const std::string &option);
        void _handle_url(const std::string &url);
        std::vector<std::string> _urls;
};
}
