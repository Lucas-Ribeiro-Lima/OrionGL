#pragma once

#include <memory.h>

namespace oriongl::core {

template <typename T> struct ResourceTraits {
    static_assert(sizeof(ResourceTraits<T>) == 0, "ResourceTraits<T> is not specialized for this resource type");
};

class ResourceSystem {
  public:
    ResourceSystem() = default;

    template <typename T, typename... Args> std::shared_ptr<T> create(Args &&...args) {
        using Traits = ResourceTraits<T>;
        using Manager = typename Traits::ManagerType;

        return Traits::create(getManager<Manager>(), std::forward<Args>(args)...);
    }

    template <typename T> std::shared_ptr<T> get(unsigned int id) {
        using Traits = ResourceTraits<T>;
        using Manager = typename Traits::ManagerType;

        return Traits::get(getManager<Manager>(), id);
    }

    template <typename T> void destroy(unsigned int resource) {
        using Traits = ResourceTraits<T>;
        using Manager = typename Traits::ManagerType;

        Traits::remove(getManager<Manager>(), resource);
    }

  private:
    template <typename Manager> Manager &getManager();
};
} // namespace oriongl::core
