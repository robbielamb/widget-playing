include Utils;

let component = ReasonReact.statelessComponent("Button");

module Color = {
  type t =
    | Primary
    | Secondary
    | Success
    | Info
    | Warning
    | Danger
    | Link;
  let toString = color =>
    switch (color) {
    | Primary => "primary"
    | Secondary => "secondary"
    | Success => "success"
    | Info => "info"
    | Warning => "warning"
    | Danger => "danger"
    | Link => "link"
    };
};

module Size = {
  type t =
    | SM
    | LG;
  let toString = size =>
    switch (size) {
    | SM => "sm"
    | LG => "lg"
    };
};

module Type = {
  type t =
    | Button
    | Submit;
  let toString = type_ =>
    switch (type_) {
    | Button => "button"
    | Submit => "sumbit"
    };
};

let mapBool = b =>
  switch (b) {
  | None => Js.Nullable.null
  | Some(t) => Js.Nullable.return(t)
  };

let make =
    (
      ~tag: string="button",
      ~active: bool=false,
      ~block: bool=false,
      ~color: Color.t=Color.Secondary,
      ~disabled: bool=false,
      ~outline: bool=false,
      ~size: option(Size.t)=?,
      ~onClick: option(ReactEvent.Mouse.t => unit)=?,
      ~type_: Type.t=Type.Button,
      ~ariaHaspopup: option(bool)=?,
      ~ariaExpanded: option(bool)=?,
      ~className: option(string)=?,
      children,
    ) => {
  ...component,
  render: _self => {
    let btnColor =
      "btn" ++ (outline ? "-outline" : "") ++ "-" ++ Color.toString(color);
    let btnSize =
      switch (size) {
      | None => ""
      | Some(size) => "btn-" ++ Size.toString(size)
      };
    let classes =
      [
        "btn",
        btnColor,
        btnSize,
        block ? "btn-block" : "",
        active ? "active" : "",
        disabled ? "disabled" : "",
        unwrapStr(i, className),
      ]
      |> String.concat(" ");
    let buttonType = Type.toString(type_);
    let props={
        "className": classes,
        "onClick": Js.Nullable.fromOption(onClick),
        "type": buttonType,
        "aria-haspopup": mapBool(ariaHaspopup),
        "aria-expanded": mapBool(ariaExpanded),
      } |. ReactDOMRe.objToDOMProps;
    ReactDOMRe.createElementVariadic(
      tag,
      ~props,
      children,
    );
  },
};

/* TODO: Make this guy work */
module DropDown = {};

module Group = {
  module Size = {
    type t =
      | SM
      | LG;
    let toString = size =>
      "btn-group"
      ++ (
        switch (size) {
        | SM => "sm"
        | LG => "lg"
        }
      );
    let unwrap = Utils.unwrapStr(toString);
  };
  let component = ReasonReact.statelessComponent("Button.Group");
  let make =
      (
        ~tag: string="div",
        ~className: option(string)=?,
        ~role: string="group",
        ~size: option(Size.t)=?,
        ~vertical: bool=false,
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        [
          Size.unwrap(size),
          vertical ? "btn-group-vertical" : "btn-group",
          unwrapStr(i, className),
        ]
        |> String.concat(" ");
      let props={"className": classes, "role": role} |. ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(
        tag,
        ~props,
        children,
      );
    },
  };
};

module Toolbar = {
  let component = ReasonReact.statelessComponent("Button.Toolbar");
  let make =
      (
        ~tag: string="div",
        ~className: option(string)=?,
        ~role: string="toolbar",
        children,
      ) => {
    ...component,
    render: _self => {
      let classes =
        ["btn-toolbar", unwrapStr(i, className)] |> String.concat(" ");
        let props={"className": classes, "role": role} |. ReactDOMRe.objToDOMProps;
      ReactDOMRe.createElementVariadic(
        tag,
        ~props,
        children,
      );
    },
  };
};
