#ifndef MSAT_CONFIGURATION_H_INCLUDED
#define MSAT_CONFIGURATION_H_INCLUDED


#define MSAT_CONFIG_PARAM(tp, name)                         \
    private:                                                \
        tp name ## _;                                       \
    public:                                                 \
        const tp &name () const { return name ## _; }       \
        void set_ ## name (const tp &val) { name ## _ = val; }

#define MSAT_LINK_PARAM(source, tp, name)                   \
    public:                                                 \
        const tp &name() const { return source.name(); }

#define MSAT_LINK_LOC_PARAM(source, tp, loc_name, name)     \
    public:                                                 \
        const tp &loc_name() const { return source.name(); }

namespace msat {

class Configuration {
    MSAT_CONFIG_PARAM(unsigned int, verbosity);

    Configuration();
    Configuration(bool bv);
    Configuration(bool bv, int language);

    bool model_generation();
    void copy_to(Configuration *dest);
    
    bool bv_;
    int language_;
private:
};

inline bool model_generation(){
    return true;
}

} // namespace msat

#undef MSAT_INHERIT_PARAM
#undef MSAT_CONFIG_PARAM

#endif // MSAT_CONFIGURATION_H_INCLUDED
