#pragma once

NS_BEG

template<typename Ty>
class InsBase
{
public:
    static std::shared_ptr<Ty> Ins(bool bIns = true)
    {
        if (bIns && _ins)
        {
            return _ins;
        }
        else if (bIns)
        {
            _ins = std::shared_ptr<Ty>(new Ty());
            _ins->OnInstantiate();
            return _ins;
        }

        try
        {
            _ins = nullptr;
        }
        catch (...)
        {
            // no op
        }
        return nullptr;
    }

    virtual void OnInstantiate() {}

private:
    static std::shared_ptr<Ty> _ins;
};

template<typename Ty>
__declspec(selectany)
std::shared_ptr<Ty> InsBase<Ty>::_ins = nullptr;

NS_END
