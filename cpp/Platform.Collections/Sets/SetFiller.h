﻿namespace Platform::Collections::Sets
{
    template<typename...> class SetFiller;
    template<Interfaces::CSet TSet, typename TReturnConstant> class SetFiller<TSet, TReturnConstant>
    {
        protected: TSet& _set;
        protected: TReturnConstant _returnConstant{};

        public: SetFiller(TSet& set, TReturnConstant returnConstant): _set(set), _returnConstant(returnConstant) { }

        public: explicit SetFiller(TSet& set) : SetFiller(set, {}) { }

        public: void Add(auto&& element) { _set.insert(std::forward<decltype(element)>(element)); }

        public: bool AddAndReturnTrue(auto&& element) { return Sets::AddAndReturnTrue(_set, std::forward<decltype(element)>(element)); }

        public: bool AddFirstAndReturnTrue(Interfaces::CArray auto&& elements) { return Sets::AddFirstAndReturnTrue(_set, elements); }

        public: bool AddAllAndReturnTrue(Interfaces::CArray auto&& elements) { return Sets::AddAllAndReturnTrue(_set, elements); }

        public: bool AddSkipFirstAndReturnTrue(Interfaces::CArray auto&& elements) { return Sets::AddSkipFirstAndReturnTrue(_set, elements); }

        public: TReturnConstant AddAndReturnConstant(auto&& element)
        {
            Add(element);
            return _returnConstant;
        }

        public: TReturnConstant AddFirstAndReturnConstant(Interfaces::CArray auto&& elements)
        {
            Sets::AddFirst(_set, elements);
            return _returnConstant;
        }

        public: TReturnConstant AddAllAndReturnConstant(Interfaces::CArray auto&& elements)
        {
            Sets::AddAll(_set, elements);
            return _returnConstant;
        }

        public: TReturnConstant AddSkipFirstAndReturnConstant(Interfaces::CArray auto&& elements)
        {
            Sets::AddSkipFirst(_set, elements);
            return _returnConstant;
        }
    };

    template<typename TSet, typename TReturnConstant>
    SetFiller(TSet, TReturnConstant) -> SetFiller<TSet, TReturnConstant>;

}
