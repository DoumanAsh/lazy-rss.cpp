#pragma once

#include <string>
#include <sstream>

/**
 * RSS Item module.
 */
namespace item {
class Item {
    public:
        ///Default constructor for empty Item.
        Item() noexcept(true);
        ///Initialization constructor of Item.
        Item(const std::string &title,
             const std::string &category,
             const std::string &link,
             const std::string &guid,
             const std::string &desc) noexcept(true);

        ///@return RSS Item title.
        const std::string& title() const;
        /**
         * Sets new value to RSS Item title.
         *
         * @param title Title of RSS Item.
         */
        Item& set_title(const std::string& title);

        ///@return RSS item category
        const std::string& category() const;
        /**
         * Sets new value to RSS Item category.
         *
         * @param category Category of RSS Item.
         */
        Item& set_category(const std::string& category);

        ///@return RSS Item link
        const std::string& link() const;
        /**
         * Sets new value to RSS Item link.
         *
         * @param link Link of RSS Item.
         */
        Item& set_link(const std::string& link);

        ///@return RSS Item guid
        const std::string& guid() const;
        /**
         * Sets new value to RSS Item guid.
         *
         * @param guid guid of RSS Item.
         */
        Item& set_guid(const std::string& guid);

        ///@return RSS Item description
        const std::string& desc() const;
        /**
         * Sets new value to RSS Item description.
         *
         * @param desc Description of RSS Item.
         */
        Item& set_desc(const std::string& desc);

        /**
         * Unsets all attributes of RSS Item.
         */
        void reset();

        /**
         * String representation of RSS Item.
         *
         * Can be used as debug information.
         */
        explicit operator std::string() const;

        /**
         * @return Whether RSS item is valid.
         *
         * @retval true If title, link and description is filled.
         * @retval false Otherwise.
         */
        operator bool() const;

        /**
         * @return Negative of bool.
         */
        bool operator !() const;

    private:
        std::string _title;
        std::string _category;
        std::string _link;
        std::string _guid;
        std::string _desc;
};

}
