add_rules("mode.debug", "mode.release", "mode.releasedbg")

set_languages("c++23")

option("commonlib")
    set_default("skyrim-commonlib-ae")
option_end()

option("build_example")
    set_default(true)
option_end()

if not has_config("commonlib") then
    return
end

if get_config("build_example") then
    add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")
    add_repositories("MrowrLib        https://github.com/MrowrLib/Packages.git")
end

add_requires(get_config("commonlib"))
add_requires("global_macro_functions")

library_name = "SkyrimScripting.Messages"

target(library_name)
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("include", { public = true }) -- Your library's own include path
    add_headerfiles("include/(**.h)")
    add_packages(get_config("commonlib"), { public = true })
    add_packages("global_macro_functions", { public = true })

if get_config("build_example") then
    mod_info = { name = "Test plugin 1 for " .. library_name }

    mods_folders = os.getenv("SKYRIM_MODS_FOLDERS")

    if mods_folders then
        mod_info.mods_folders = mods_folders
    else
        print("SKYRIM_MODS_FOLDERS environment variable not set")
    end

    commonlib_version = get_config("commonlib"):match("skyrim%-commonlib%-(.*)")

    target("_SksePlugin_1")
        set_basename(mod_info.name .. "-" .. commonlib_version)
        add_files("plugin1.cpp")
        add_rules("@" .. get_config("commonlib") .. "/plugin", {
            mod_name = mod_info.name .. " (" .. commonlib_version .. ")",
            mods_folders = mod_info.mods_folders or "",
            mod_files = mod_info.mod_files,
            name = mod_info.name
        })
        add_deps(library_name)
        
    mod_info.name = "Test plugin 2 for " .. library_name

    target("_SksePlugin_2")
        set_basename(mod_info.name .. "-" .. commonlib_version)
        add_files("plugin2.cpp")
        add_rules("@" .. get_config("commonlib") .. "/plugin", {
            mod_name = mod_info.name .. " (" .. commonlib_version .. ")",
            mods_folders = mod_info.mods_folders or "",
            mod_files = mod_info.mod_files,
            name = mod_info.name
        })
        add_deps(library_name)
end