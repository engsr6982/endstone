import sys
from typing import BinaryIO, Optional, List

# noinspection PyProtectedMember
from endstone._bindings import PluginDescription, Permission, PermissionDefault

from endstone.command import Command

if sys.version_info >= (3, 11):
    # noinspection PyUnresolvedReferences
    from tomllib import load
else:
    from tomli import load


class PluginDescriptionFile(PluginDescription):
    def __init__(self, fp: BinaryIO):
        data = load(fp)

        try:
            name = data.pop("name")
            version = data.pop("version")
            main = data.pop("main")
            PluginDescription.__init__(self, name, version)
        except KeyError as e:
            raise RuntimeError(f"Invalid plugin.toml: {e} is not defined") from e

        self._main: str = main
        self._description: Optional[str] = None
        self._authors: Optional[list[str]] = None
        self._prefix: Optional[str] = None
        self._commands: list[Command] = []
        self._permissions: list[Permission] = []
        self._default_permission: Optional[PermissionDefault] = None

        for k, v in data.items():
            if k == "commands":
                self._commands = self._load_commands(v)
                continue

            if k == "permissions":
                self._permissions = self._load_permissions(v, Permission.DEFAULT_PERMISSION)
                continue

            if k == "default-permission":
                self._default_permission = PermissionDefault.get_by_name(str(v).lower())
                continue

            if hasattr(self, f"_{k}"):
                setattr(self, f"_{k}", v)

    def _load_commands(self, command_map: dict) -> list[Command]:
        commands = []
        for name, value in command_map.items():
            if ":" in name:
                raise NameError(f"Could not load command {name} for plugin {self.name}: Illegal Characters")

            command = Command(name)

            description = value.get("description", None)
            usages = value.get("usages", None)
            aliases = value.get("aliases", None)
            permission = value.get("permission", None)

            if description:
                command.description = description

            if usages:
                if isinstance(usages, list):
                    usage_list = usages
                else:
                    usage_list = [usages]

                command.usages = usage_list

            if aliases:
                alias_list = []

                if isinstance(aliases, list):
                    for alias in aliases:
                        if ":" in alias:
                            raise NameError(f"Could not load alias {alias} for plugin {self.name}: Illegal Characters")

                        alias_list.append(alias)
                else:
                    if ":" in aliases:
                        raise NameError(f"Could not load alias {aliases} for plugin {self.name}: Illegal Characters")

                    alias_list.append(aliases)

                command.aliases = alias_list

            if permission:
                command.permission = permission

            commands.append(command)

        return commands

    def _load_permissions(self, permission_map: dict, default: PermissionDefault) -> list[Permission]:
        result = []
        for k, v in permission_map.items():
            result.append(self._load_permission(k, v, default, result))

        return result

    def _load_permission(self, name: str, data: dict, default: PermissionDefault, output: list) -> Permission:
        assert name is not None and len(name) != 0, "Name must not be null or empty"

        description = None
        children = {}

        for k, v in data.items():
            if k == "default":
                # Convert the value to a string and make it lowercase for a case-insensitive match
                # noinspection PyArgumentList
                value = PermissionDefault.get_by_name(str(v).lower())
                if value:
                    default = value
                else:
                    raise ValueError(f"'default' key contained unknown value: {v}")

            elif k == "description":
                description = str(v)

            else:
                # Check if it is a leaf node
                if isinstance(v, bool):
                    children[f"{name}.{k}"] = v

                # Check if it is a subtree
                elif isinstance(v, dict):
                    permission = self._load_permission(f"{name}.{k}", v, default, output)
                    children[permission.name] = True
                    output.append(permission)

                else:
                    raise TypeError(f"Permission node {name}.{k} has wrong type {type(v)}")

        return Permission(name, description, default, children)

    @property
    def main(self) -> str:
        return self._main

    @property
    def description(self) -> Optional[str]:
        return self._get_description()

    @property
    def authors(self) -> Optional[list[str]]:
        return self._get_authors()

    @property
    def prefix(self) -> Optional[str]:
        return self._get_prefix()

    @property
    def commands(self) -> list[Command]:
        return self._get_commands()

    @property
    def permissions(self) -> list[Permission]:
        return self._get_permissions()

    @property
    def default_permission(self) -> Optional[PermissionDefault]:
        return self._get_default_permission()

    def _get_description(self) -> Optional[str]:
        return self._description

    def _get_authors(self) -> Optional[list[str]]:
        return self._authors

    def _get_prefix(self) -> Optional[str]:
        return self._prefix

    def _get_commands(self) -> list[Command]:
        return self._commands

    def _get_permissions(self) -> list[Permission]:
        return self._permissions

    def _get_default_permission(self) -> Optional[PermissionDefault]:
        return self._default_permission
