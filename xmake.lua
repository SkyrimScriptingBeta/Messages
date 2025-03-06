add_rules("mode.debug", "mode.release", "mode.releasedbg")

set_languages("c++23")

option("commonlib")
    set_description("Which CommonLib package to use")
    set_default("skyrim-commonlib-ae")
option_end()

option("require_commonlib")
    set_description("If true, add_requires the CommonLib package")
    set_default(true)
option_end()

option("include_repo_skyrimscripting")
    set_description("If true, add the SkyrimScripting repository during build")
    set_default(true)
option_end()

option("include_repo_skyrimscripting_beta")
    set_description("If true, add the SkyrimScripting Beta repository during build")
    set_default(true)
option_end()

option("include_repo_mrowrlib")
    set_description("If true, add the MrowrLib repository during build")
    set_default(true)
option_end()

option("build_example")
    set_description("Build example project using this library")
    set_default(true)
option_end()

option("build_papyrus_scripts")
    set_description("Build Papyrus scripts")
    set_default(false)
option_end()

option("use_log_library")
    set_description("If true, builds with support for the _Log_ library")
    set_default(false)
option_end()

library_name = "SkyrimScripting.Messages"

-- Example SKSE plugin using the static library
mod_info = {
    name = "Test plugin for " .. library_name,
    version = "0.0.1",
    author = "Mrowr Purr",
    email = "mrowr.purr@gmail.com",
    mod_files = {"Scripts"}
}

-- skyrim_versions = {"ng"}
skyrim_versions = {"ae"}
-- skyrim_versions = {"ae", "se", "ng", "vr"}

if has_config("include_repo_skyrimscripting") then
    add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")
end

if has_config("include_repo_skyrimscripting_beta") then
    add_repositories("SkyrimScriptingBeta https://github.com/SkyrimScriptingBeta/Packages.git")
end

if has_config("include_repo_mrowrlib") then
    add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
end

if has_config("require_commonlib") then
    add_requires(get_config("commonlib"))
end

add_requires("global_macro_functions")

if has_config("use_log_library") then
    add_requires("_Log_")
end

if has_config("commonlib") then
    print("Building using CommonLib package: " .. get_config("commonlib"))
    target(library_name)
        set_kind("static")
        add_files("src/*.cpp")
        add_includedirs("include", { public = true }) -- Your library's own include path
        add_headerfiles("include/(**.h)")
        if has_config("commonlib") then
            add_packages(get_config("commonlib"), { public = true })
        end
        add_packages("global_macro_functions", { public = true })
end

if has_config("build_example") then
    print("Building example project")
    includes("skse.lua")
end

if has_config("build_papyrus_scripts") then
    includes("papyrus.lua")
end
