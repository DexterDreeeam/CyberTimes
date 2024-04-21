#pragma once

NS_BEG

template<typename Ty>
class InsBase
{
public:
    template <typename ...Tys>
    static std::shared_ptr<Ty> Ins(Tys... tys)
    {
        if (_ins)
        {
            return _ins;
        }

        _ins = std::shared_ptr<Ty>(new Ty(tys...));
        _ins->OnInstantiate();
        return _ins;
    }

    static void Deins()
    {
        try
        {
            _ins = nullptr;
        }
        catch (...)
        {
            // no op
        }
    }

    virtual void OnInstantiate() {}

private:
    static std::shared_ptr<Ty> _ins;
};

template<typename Ty>
__declspec(selectany)
std::shared_ptr<Ty> InsBase<Ty>::_ins = nullptr;

NS_END
