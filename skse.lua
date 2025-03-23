add_rules("mode.debug", "mode.release")

set_languages("c++23")

add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")

mods_folders = os.getenv("SKYRIM_MODS_FOLDERS")

if mods_folders then
    mod_info.mods_folders = mods_folders
else
    print("SKYRIM_MODS_FOLDERS environment variable not set")
end

add_requires("SKSE::log::info")

for _, game_version in ipairs(skyrim_versions) do
    add_requires("skyrim-commonlib-" .. game_version)
    add_requires("SkyrimScripting.Logging", { configs = { commonlib = "skyrim-commonlib-" .. game_version, useSKSE::log::infolibrary = true, use_skse_plugin_info_library = true, use_skyrimscripting_entrypoint = true, include_repo_mrowrlib = true }})
end

for _, game_version in ipairs(skyrim_versions) do
    target("StaticLibrary-" .. game_version:upper())
        set_kind("static")
        add_files("src/*.cpp")
        add_includedirs("include", { public = true }) -- Your library's own include path
        add_packages("skyrim-commonlib-" .. game_version)
        add_packages("global_macro_functions", { public = true })
end

number_of_plugins = 2
for plugin_number = 1, number_of_plugins do
    for _, game_version in ipairs(skyrim_versions) do
        target("_SksePlugin-" .. game_version:upper() .. "-" .. plugin_number)
            set_basename(mod_info.name .. "-" .. plugin_number .. "-" .. game_version:upper())
            add_files("plugin" .. plugin_number .. ".cpp")
            add_packages("skyrim-commonlib-" .. game_version)
            add_rules("@skyrim-commonlib-" .. game_version .. "/plugin", {
                mod_name = mod_info.name .. "-" .. plugin_number .. " (" .. game_version:upper() .. ")",
                mods_folders = mod_info.mods_folders or "",
                mod_files = mod_info.mod_files,
                name = mod_info.name .. "-" .. plugin_number,
                version = mod_info.version,
                author = mod_info.author,
                email = mod_info.email
            })
            add_deps("StaticLibrary-" .. game_version:upper())
            add_packages("SKSE::log::info", "SkyrimScripting.Logging", { public = true })
    end
end
