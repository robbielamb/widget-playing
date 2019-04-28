include Utils;

module Fixed = {
  type t =
    | Top
    | Bottom;
  let toString = fixed =>
    switch (fixed) {
    | Top => "top"
    | Bottom => "bottom"
    };
};

[@react.component]
let make =
    (
      ~light: bool=false,
      ~fixed: option(Fixed.t)=?,
      ~sticky: option(string)=?,
      ~color: option(ColorsRe.Background.t)=?,
      ~role: option(string)=?,
      ~className: option(string)=?,
      ~toggleable: bool=false,
      ~children,
    ) => {
  let fixedClass = (cls: option(Fixed.t)) =>
    switch (cls) {
    | None => ""
    | Some(x) => "fixed-" ++ Fixed.toString(x)
    };
  let stickyClass = (cls: option(string)) =>
    switch (cls) {
    | None => ""
    | Some(x) => "sticky-" ++ x
    };
  let className =
    [
      "navbar",
      toggleable ? "navbar-toggleable" : "",
      light ? "navbar-light" : "navbar-dark",
      unwrapStr(ColorsRe.Background.toString, color),
      fixedClass(fixed),
      stickyClass(sticky),
      unwrapStr(i, className),
    ]
    |> String.concat(" ");
  <nav className ?role> children </nav>;
};

module Brand = {
  [@react.component]
  let make = (~className: option(string)=?, ~href: string="", ~children) => {
    let className =
      ["navbar-brand", unwrapStr(i, className)] |> String.concat(" ");
    <a className href> children </a>;
  };
};

module Toggler = {
  [@react.component]
  let make =
      (
        ~tag: string="button",
        ~type_: string="button",
        ~onClick: option(ReactEvent.Mouse.t => unit),
        ~className: string="",
      ) => {
    let span = <span className="navbar-toggler-icon" />;
    let className = ["navbar-toggler", className] |> String.concat(" ");

    ReactDOMRe.createElementVariadic(
      tag,
      ~props=
        {"type": type_, "className": className, "onClick": onClick}
        ->ReactDOMRe.objToDOMProps,
      [|span|],
    );
  };
};

/* cssModule::(cssModule: option (Js.t {..}))=? */

/* cssModule::(cssModule: option (Js.t {..}))=? */