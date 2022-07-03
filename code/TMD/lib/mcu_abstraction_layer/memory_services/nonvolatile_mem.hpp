
#ifndef __NONVOLATILE_MEM__
#define __NONVOLATILE_MEM__
#include <string>

namespace nvs {
    /*!
    * Type of variable stored in the NVS.
    *
    * Supported types are:
    * - unsigned integers, from 8 bit to 64 bit,
    * - signed integers, from 8 bit to 64 bit,
    * - std::string
    */
    template <typename basictype>
    class NVServices {
        private:
            /*!
            * Private default constructor, to prevent object from being instantiated.
            */
            NVServices() = default;
        public:
            /*!
            * Perform a store to a NVS of a given key - value pair.
            *
            * Type of value must be supported!
            * @param key Tag under which the specified value will be stored.
            * @param value Value to be stored. Must be of compatible type.
            */
            static esp_err_t nvs_store_key_val_pair(const std::string& key, basictype value);
    };
}

#endif /* __NONVOLATILE_MEM__ */