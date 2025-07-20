#pragma once
#include <string>
#include <memory>
#include <vector>
#include <optional>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

class IJson {
public:
    virtual ~IJson() = default;

    virtual std::optional<std::string> getString(const std::string& key) const = 0;
    virtual std::optional<double> getDouble(const std::string& key) const = 0;
    virtual std::optional<int> getInt(const std::string& key) const = 0;
    virtual std::optional<bool> getBool(const std::string& key) const = 0;

    //virtual std::shared_ptr<IJson> getObject(const std::string& key) const = 0;
   // virtual std::vector<std::shared_ptr<IJson>> getArray(const std::string& key) const = 0;

    static std::shared_ptr<IJson> parse(const std::string& jsonStr);
};


class RapidJsonAdaptor : public IJson {
public:

    std::optional<std::string> getString(const std::string& key) const override {
        if (value_.HasMember(key.c_str()) && value_[key.c_str()].IsString())
            return value_[key.c_str()].GetString();
        return std::nullopt;
    }

    std::optional<double> getDouble(const std::string& key) const override {
        if (value_.HasMember(key.c_str()) && value_[key.c_str()].IsDouble())
            return value_[key.c_str()].GetDouble();
        return std::nullopt;
    }

    std::optional<int> getInt(const std::string& key) const override {
        if (value_.HasMember(key.c_str()) && value_[key.c_str()].IsInt())
            return value_[key.c_str()].GetInt();
        return std::nullopt;
    }

    std::optional<bool> getBool(const std::string& key) const override {
        if (value_.HasMember(key.c_str()) && value_[key.c_str()].IsBool())
            return value_[key.c_str()].GetBool();
        return std::nullopt;
    }

    static std::shared_ptr<IJson> parse(const std::string& jsonStr) {
        auto doc = std::make_shared<rapidjson::Document>();
        if (doc->Parse(jsonStr.c_str()).HasParseError()) {
            throw std::runtime_error("Invalid JSON");
        }
        return std::shared_ptr<IJson>(new RapidJsonAdaptor(*doc, doc));
    }

private:
    const rapidjson::Value& value_;
    std::shared_ptr<rapidjson::Document> root_;
    RapidJsonAdaptor(const rapidjson::Value& value, std::shared_ptr<rapidjson::Document> root)
        : value_(value), root_(std::move(root)) {}
};
