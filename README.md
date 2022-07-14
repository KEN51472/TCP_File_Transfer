# TCP_File_Transfer

简单的tcp文件传输项目

部署与安装
---
安装json_spirit

    cd TCP_File_Transfer
    git clone https://github.com/cierelabs/json_spirit.git
    cd json_spirit
    mkdir build
    cd build
    cmake ..
    make

编译tcp_file_transfer
    
    cd TCP_File_Transfer
    make
    make clean

vscode相关配置
---

tasks.json

    {
        "tasks": [
            {
                "type": "cppbuild",
                "label": "C/C++: g++ 生成活动文件",
                "command": "/usr/bin/g++",
                "args": [
                    "-fdiagnostics-color=always",
                    "-g",
                    "${file}",
                    "-o",
                    "${fileDirname}/${fileBasenameNoExtension}",
                    "${fileDirname}/controller/client_trans_controller.cpp",
                    "${fileDirname}/controller/server_trans_controller.cpp",
                    "${fileDirname}/inputer/cin_data_inputer.cpp",
                    "${fileDirname}/inputer/session_data_inputer.cpp",
                    "${fileDirname}/inputer/data_inputer.cpp",
                    "${fileDirname}/reader/data_reader.cpp",
                    "${fileDirname}/reader/file_data_reader.cpp",
                    "${fileDirname}/reader/remote_data_reader.cpp",
                    "${fileDirname}/writer/data_writer.cpp",
                    "${fileDirname}/writer/remote_data_writer.cpp",
                    "${fileDirname}/writer/file_data_writer.cpp",
                    "${fileDirname}/session/client_session.cpp",
                    "${fileDirname}/session/server_session.cpp",
                    "${fileDirname}/session/io_session.cpp",
                    "-I",
                    "${fileDirname}/inputer",
                    "-I",
                    "${fileDirname}/reader",
                    "-I",
                    "${fileDirname}/writer",
                    "-I",
                    "${fileDirname}/controller",
                    "-I",
                    "${fileDirname}/session",
                    "-lpthread"
                ],
                "options": {
                    "cwd": "${fileDirname}"
                },
                "problemMatcher": [
                    "$gcc"
                ],
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "detail": "调试器生成的任务。"
            }
        ],
        "version": "2.0.0"
    }



launch.json

    {
        // 使用 IntelliSense 了解相关属性。 
        // 悬停以查看现有属性的描述。
        // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
        "version": "0.2.0",
        "configurations": [
            {
                "name": "Client",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/client",
                "args": [
                    "-g",
                    "${workspaceFolder}/client"
                ],
                "stopAtEntry": false,
                "cwd": "${fileDirname}",
                "environment": [],
                "externalConsole": false,
                "MIMode": "gdb",
                "setupCommands": [
                    {
                        "description": "为 gdb 启用整齐打印",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    },
                    {
                        "description":  "将反汇编风格设置为 Intel",
                        "text": "-gdb-set disassembly-flavor intel",
                        "ignoreFailures": true
                    }
                ]
            },
            {
                "name": "Server",
                "type": "cppdbg",
                "request": "launch",
                "program": "${workspaceFolder}/server",
                "args": [
                    "-g",
                    "${workspaceFolder}/server"
                ],
                "stopAtEntry": false,
                "cwd": "${fileDirname}",
                "environment": [],
                "externalConsole": false,
                "MIMode": "gdb",
                "setupCommands": [
                    {
                        "description": "为 gdb 启用整齐打印",
                        "text": "-enable-pretty-printing",
                        "ignoreFailures": true
                    },
                    {
                        "description":  "将反汇编风格设置为 Intel",
                        "text": "-gdb-set disassembly-flavor intel",
                        "ignoreFailures": true
                    }
                ]
            }

        ]
    }