#pragma once
#include <string>
#include <memory>
#include <vector>
#include <optional>

class IJson {
public:
    virtual ~IJson() = default;

    virtual std::optional<std::string> getString(const std::string& key) const = 0;
    virtual std::optional<double> getDouble(const std::string& key) const = 0;
    virtual std::optional<int> getInt(const std::string& key) const = 0;
    virtual std::optional<bool> getBool(const std::string& key) const = 0;

    virtual std::shared_ptr<IJson> getObject(const std::string& key) const = 0;
    virtual std::vector<std::shared_ptr<IJson>> getArray(const std::string& key) const = 0;

    static std::shared_ptr<IJson> parse(const std::string& jsonStr);
};
