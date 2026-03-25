#pragma once

#include <string>

namespace RmlTests
{
	namespace InlineRmls
	{
		const std::string rmlSample = R"RML(<rml>
    <head>
        <title>Inline RmlUi Test</title>
        <style>
            *{
                font-family: Roboto-Medium; 
                font-size:16px;
            }
        </style>
    </head>
    <body font-family="Roboto">
        <div id="container" class="main-container">
            <h1>Welcome to RmlUi Inline Test</h1>
            <p>This is a paragraph rendered directly from C++ string.</p>

            <button onclick="alert('Button clicked!')">Click Me</button>

            <ul>
                <li>Item One</li>
                <li>Item Two</li>
                <li>Item Three</li>
            </ul>
        </div>
    </body>
</rml>
)RML";
        const std::string rcssSample = R"RCSS(
* {
    font-family: "Roboto", sans-serif;
    font-size: 16px;
    color: #ffffff;
}
)RCSS";
	}
}