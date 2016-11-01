#include "item.hpp"

using namespace item;

Item::Item() noexcept(true) {
}

Item::Item(const std::string &title,
           const std::string &category,
           const std::string &link,
           const std::string &guid,
           const std::string &desc) noexcept(true)

    :
    _title(title),
    _category(category),
    _link(link),
    _guid(guid),
    _desc(desc)
{
}

const std::string& Item::title() const {
    return _title;
}
Item& Item::set_title(const std::string& title) {
    _title = title;
    return *this;
}

const std::string& Item::category() const {
    return _category;
}
Item& Item::set_category(const std::string& category) {
    _category = category;
    return *this;
}

const std::string& Item::link() const {
    return _link;
}
Item& Item::set_link(const std::string& link) {
    _link = link;
    return *this;
}

const std::string& Item::guid() const {
    return _guid;
}
Item& Item::set_guid(const std::string& guid) {
    _guid = guid;
    return *this;
}

const std::string& Item::desc() const {
    return _desc;
}
Item& Item::set_desc(const std::string& desc) {
    _desc = desc;
    return *this;
}

void Item::reset() {
    _title.clear();
    _category.clear();
    _link.clear();
    _guid.clear();
    _desc.clear();
}

Item::operator std::string() const {
    std::ostringstream stream;

    stream << "RSS (title='" << _title
           << "', category='" << _category
           << "', link='" << _link
           << "', guid='" << _guid
           << "', desc='" << _desc
           << "')";

    return stream.str();
}

Item::operator bool() const {
    return (!_title.empty()) and (!_link.empty()) and (!_desc.empty());
}

Item::operator !() const {
    return (_title.empty()) or (_link.empty()) or (_desc.empty());
}
