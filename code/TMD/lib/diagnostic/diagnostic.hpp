
#ifndef __DIAGNOSTIC__
#define __DIAGNOSTIC__

#include <stdexcept>
extern "C" {
    #include "esp_err.h"
}


namespace diagnostic {
    class DiagnosticUtils {
        private:
            /*!
            * Private default constructor to prevent init of the instance.
            */
            DiagnosticUtils() = default;
        public:
            /*!
            * Prepares error message for thrown exception.
            *
            * @param base The beginning of the message and the basis for error type recognition.
            * @param context More information about in what conditions the exception was triggered.
            * @param error Number of error returned by the native C function.
            * @return Constructed string.
            */
            static std::string prepare_error_msg(const std::string& base,
                                                const std::string& context,
                                                esp_err_t error);
    };

    class I2C_NotInitializedException : public std::logic_error {
        public:
            I2C_NotInitializedException(esp_err_t error_code, const std::string& context) : 
            std::logic_error(
                DiagnosticUtils::prepare_error_msg("ERROR: I2C init failed; ", context, error_code)
                ){};

    };
    class I2C_MasterSlaveReadFailedException : public std::logic_error {
        public:
            I2C_MasterSlaveReadFailedException(esp_err_t error_code, const std::string& context) :
            std::logic_error(
                DiagnosticUtils::prepare_error_msg("ERROR: I2C master read from slave failed; ",
                                                    context, error_code)
                ){};
    };

    class I2C_MasterSlaveWriteFailedException : public std::logic_error {
        public:
            I2C_MasterSlaveWriteFailedException(esp_err_t error_code, const std::string& context) :
            std::logic_error(
                DiagnosticUtils::prepare_error_msg("ERROR: I2C master write to slave failed; ",
                                                    context, error_code)
                ){};
    };

    class Sensirion_SHT4X_CRC8ChecksumMismatchException : public std::logic_error {
        public:
            Sensirion_SHT4X_CRC8ChecksumMismatchException(const std::string& context) :
            std::logic_error("ERROR: Transmission from SHT4X sensor faulty, CRC not matching! " +
            context){};
    };

    class NotImplementedException : public std::logic_error {
        public:
            NotImplementedException(const std::string& context) :
            std::logic_error("ERROR: functionality not yet implemented! Context: " + context){};
    };
}

#endif