#pragma once
#include <string>
#include <functional>

class GLFWwindow;

namespace LifeExe
{

struct WindowId
{
    unsigned int value{0};
    constexpr explicit WindowId(unsigned int id) : value(id) {}

    constexpr WindowId operator++(int)
    {
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=>(const WindowId&) const = default;// in fact only = is needed
    // to use WindowId as key in unordered_map; here is new syntacis what defines all 6 comparisons
};

struct WindowSettings
{
    std::string title{};
    int width{800};
    int height{600};
    int x{50};
    int y{50};
};

class GLFWWindow final
{
public:
    GLFWWindow(const WindowSettings& settings);
    ~GLFWWindow();

    void setTitle(const std::string& title);
    bool isValid() const;
    bool shouldClose() const;

private:
    GLFWwindow* m_window{nullptr};
};

}  // namespace LifeExe

namespace std
{
template <>
struct hash<LifeExe::WindowId> // hash function for WindowId as Key  in map, using the same default hash for inteter id
{
    size_t operator()(const LifeExe::WindowId& id) const noexcept  //
    {
        return std::hash<unsigned int>{}(id.value);
    }
};
}  // namespace std