from typing import TextIO, List, Literal
import yaml
from dataclasses import dataclass

@dataclass(frozen=True)
class Config:
    name: str
    version: str
    author: str
    entrypoint: str
    targets: List[Literal["VST3", "AU", "STANDALONE"]]

    @staticmethod
    def check_config(config):
        required_keys = ["name", "version", "author", "entrypoint", "targets"]
        for key in required_keys:
            if key not in config:
                raise Exception("Config is missing required key: " + key)

    @classmethod
    def from_yaml(cls, file_handle: TextIO):
        config = yaml.safe_load(file_handle)
        cls.check_config(config)
        return cls(
            name=config["name"],
            version=config["version"],
            author=config["author"],
            entrypoint=config["entrypoint"],
            targets=config["targets"]
        )
