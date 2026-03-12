#include <iostream>

#include <unordered_map> 
#include <memory>   
#include <typeindex>


class VECTOR
{
private:
    float x, y, z;

public:
    VECTOR() :x(0.0f), y(0.0f), z(0.0f) {};
    explicit VECTOR(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
    explicit VECTOR(float _scl) : x(_scl), y(_scl), z(_scl) {};
    ~VECTOR() {};

    void set(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    VECTOR &get()
    {
        return *this;
    }
};

class Component
{
protected:
    int m_ID = 0;
public:
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void LateUpdate() {};
    virtual void Draw() {};

    void set_ID(const int _id) { m_ID = _id; }
    int get_ID()const { return m_ID; }
};

class Component01 : public Component{public:void Start()override {}; void Update()override {};};
class Component02 : public Component{public:void Start()override {}; void Update()override {};};
class Component03 : public Component{public:void Start()override {}; void Update()override {};};
class Component04 : public Component{public:void Start()override {}; void Update()override {};};
class Component05 : public Component{public:void Start()override {}; void Update()override {};};
class Component06 : public Component{public:void Start()override {}; void Update()override {};};
class Component07 : public Component{public:void Start()override {}; void Update()override {};};
class Component08 : public Component{public:void Start()override {}; void Update()override {};};
class Component09 : public Component{public:void Start()override {}; void Update()override {};};
class Component10 : public Component{public:void Start()override {}; void Update()override {};};
class Component11 : public Component{public:void Start()override {}; void Update()override {};};
class Component12 : public Component{public:void Start()override {}; void Update()override {};};
class Component13 : public Component{public:void Start()override {}; void Update()override {};};
class Component14 : public Component{public:void Start()override {}; void Update()override {};};
class Component15 : public Component{public:void Start()override {}; void Update()override {};};
class Component16 : public Component{public:void Start()override {}; void Update()override {};};
class Component17 : public Component{public:void Start()override {}; void Update()override {};};
class Component18 : public Component{public:void Start()override {}; void Update()override {};};
class Component19 : public Component{public:void Start()override {}; void Update()override {};};
class Component20 : public Component{public:void Start()override {}; void Update()override {};};

class GameObject
{
private:
    std::unordered_map<std::type_index, std::shared_ptr<Component>> m_ComponentMap;
    std::vector<std::shared_ptr<Component>>m_Components;

public:
    void Start()
    {
        for (auto &comp : m_ComponentMap)
        {
            if (!comp.second)continue;
            comp.second->Start();
        }
    }
    void Update()
    {
        for (auto &comp : m_ComponentMap)
        {
            if (!comp.second)continue;
            comp.second->Update();
        }
    }
    void LateUpdate()
    {
        for (auto &comp : m_ComponentMap)
        {
            if (!comp.second)continue;
            comp.second->LateUpdate();
        }
    }
    void Draw()
    {
        for (auto &comp : m_ComponentMap)
        {
            if (!comp.second)continue;
            comp.second->Draw();
        }
    }

    template<typename T, typename ...Args>
    std::shared_ptr<T>  AddComponent(Args&& ...args)
    {
        auto comp = std::make_shared<T>(std::forward<Args>(args)...);
        m_ComponentMap[std::type_index(typeid(T))] = comp;
        return comp;
    }

    template<typename T, typename ...Args>
    std::shared_ptr<T>  AddComponentD(Args&& ...args)
    {
        auto comp = std::make_shared<T>(std::forward<Args>(args)...);
        m_Components.push_back(comp);
        return comp;
    }

    template<typename T>
    std::shared_ptr<T> GetComponent()
    {
        auto typeIdx = std::type_index(typeid(T));
        auto it = m_ComponentMap.find(typeIdx);
        if (it != m_ComponentMap.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    std::shared_ptr<T> GetComponentD()
    {
        for (auto &comp : m_Components)
        {
             auto target =  std::dynamic_pointer_cast<T>(comp);
             if (target != nullptr)
             {
                 return target;
             }
        }
        return nullptr;
    }

    template<typename T>
    void RemoveComponent()
    {
        m_ComponentMap.erase(std::type_index(typeid(T)));
    }

    template<typename T>
    void RemoveComponentD()
    {
        auto begin = m_Components.begin();
        auto end = m_Components.end();

        m_Components.erase(std::remove_if(begin, end,
            [](const std::shared_ptr<Component> &comp)
            {
                return (std::dynamic_pointer_cast<T>(comp) != nullptr);
            }),
            end
        );
    }
};

const int g_TestMax = 1000000;

void dynamic_test(GameObject& obj)
{
    obj.AddComponentD<Component01>();
    obj.AddComponentD<Component02>();
    obj.AddComponentD<Component03>();
    obj.AddComponentD<Component04>();
    obj.AddComponentD<Component05>();
    obj.AddComponentD<Component06>();
    obj.AddComponentD<Component07>();
    obj.AddComponentD<Component08>();
    obj.AddComponentD<Component09>();
    obj.AddComponentD<Component10>();
    obj.AddComponentD<Component11>();
    obj.AddComponentD<Component12>();
    obj.AddComponentD<Component13>();
    obj.AddComponentD<Component14>();
    obj.AddComponentD<Component15>();
    obj.AddComponentD<Component16>();
    obj.AddComponentD<Component17>();
    obj.AddComponentD<Component18>();
    obj.AddComponentD<Component19>();
    obj.AddComponentD<Component20>();

    // dynamic 
    for (int i = 0; i < g_TestMax; i++)
    {
        auto comp = obj.GetComponentD<Component20>();
        obj.Update();
        obj.Draw();
    }
}

void static_test(GameObject &obj)
{
    obj.AddComponent<Component01>();
    obj.AddComponent<Component02>();
    obj.AddComponent<Component03>();
    obj.AddComponent<Component04>();
    obj.AddComponent<Component05>();
    obj.AddComponent<Component06>();
    obj.AddComponent<Component07>();
    obj.AddComponent<Component08>();
    obj.AddComponent<Component09>();
    obj.AddComponent<Component10>();
    obj.AddComponent<Component11>();
    obj.AddComponent<Component12>();
    obj.AddComponent<Component13>();
    obj.AddComponent<Component14>();
    obj.AddComponent<Component15>();
    obj.AddComponent<Component16>();
    obj.AddComponent<Component17>();
    obj.AddComponent<Component18>();
    obj.AddComponent<Component19>();
    obj.AddComponent<Component20>();

    // static 
    for (int i = 0; i < g_TestMax; i++)
    {
        auto comp = obj.GetComponent<Component20>();
        obj.Update();
        obj.Draw();
    }
}

int main() {

    VECTOR vecA(0, 0, 0);

    GameObject obj;
    static_test(obj);
    dynamic_test(obj);
    
    //std::cout << comp->get_Hoge() << std::endl;

    return 0;
}