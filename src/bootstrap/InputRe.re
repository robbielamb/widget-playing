include Utils;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString = size =>
    switch (size) {
    | None => ""
    | Large => "form-control-lg"
    | Small => "form-control-sm"
    };
};

type inputType =
  | Button
  | Checkbox
  | Date
  | Email
  | File
  | Password
  | Radio
  | Reset
  | Select
  | Submit
  | Text
  | TextArea
  | Url;

let component = ReasonReact.statelessComponent("Input");

let make =
    (
      ~tag: string="input",
      ~id: option(string)=?,
      ~name: string="",
      ~type_: inputType=Text,
      ~size: Size.t=Size.None,
      ~plainText: bool=false,
      ~placeholder: option(string)=?,
      ~disabled: bool=false,
      ~multiple: option(bool)=?,
      ~className: option(string)=?,
      ~onInput: option(ReactEvent.Keyboard.t => unit)=?,
      ~onChange: option(ReactEvent.Form.t => unit)=?,
      ~onBlur: option(ReactEvent.Focus.t => unit)=?,
      ~checked: option(bool)=?,
      ~valid: option(bool)=?,
      ~value: option(string)=?,
      ~required: bool=false,
      children,
    ) => {
  ...component,
  render: _self => {
    let checkInput =
      switch (type_) {
      | Radio => true
      | Checkbox => true
      | _ => false
      };
    let fileInput = type_ === File;
    let tag =
      switch (type_) {
      | TextArea => "textarea"
      | Select => "select"
      | _ => tag
      };
    let typeAttribute =
      switch (type_) {
      | Button => "button"
      | Checkbox => "checkbox"
      | Date => "date"
      | Email => "email"
      | File => "file"
      | Password => "password"
      | Radio => "radio"
      | Reset => "reset"
      | Select => ""
      | Submit => "submit"
      | TextArea => ""
      | Text => "text"
      | Url => "url"
      };
    let formControlClass =
      switch (plainText, fileInput, checkInput) {
      | (true, false, false) => "form-control-planetext"
      | (false, true, false) => "form-control-file"
      | (false, false, true) => "form-check-input"
      | (_, _, _) => "form-control"
      };
    let validClassName =
      switch (valid) {
      | None => ""
      | Some(true) => "is-valid"
      | Some(false) => "is-invalid"
      };
    let className =
      [
        unwrapStr(i, className),
        Size.toString(size),
        formControlClass,
        validClassName,
      ]
      |> String.concat(" ");
    let props = {
      "className": className,
      "id": Js.Nullable.fromOption(id),
      "name": name,
      "type": typeAttribute,
      "placeholder": Js.Nullable.fromOption(placeholder),
      "multiple": Js.Nullable.fromOption(multiple),
      "disabled": disabled,
      "onInput": Js.Nullable.fromOption(onInput),
      "onChange": Js.Nullable.fromOption(onChange),
      "onBlur": Js.Nullable.fromOption(onBlur),
      "checked": Js.Nullable.fromOption(checked),
      "value": Js.Nullable.fromOption(value),
      "required": required,
    } |. ReactDOMRe.objToDOMProps;
    ReactDOMRe.createElementVariadic(tag, ~props, children);
  },
};

module Label = {
  include LayoutRe.ColSizes;
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
  let component = ReasonReact.statelessComponent("Form.Label");
  let make =
      (
        ~tag: string="label",
        ~for_: option(string)=?,
        ~hidden: bool=false,
        ~check: bool=false,
        ~inline: bool=false,
        ~disabled: bool=false,
        ~size: option(Size.t)=?,
        ~color: option(ColorsRe.Text.t)=?,
        ~xs: option(shape)=Some(shape()),
        ~sm: option(shape)=?,
        ~md: option(shape)=?,
        ~lg: option(shape)=?,
        ~xl: option(shape)=?,
        ~className: option(string)=?,
        children,
      ) => {
    ...component,
    render: _self => {
      let colClasses = processShapeList(xs, sm, md, lg, xl);
      let containsColClasses = Belt.List.length(colClasses) > 0;
      let classes =
        [
          unwrapStr(i, className),
          hidden ? "sr-only" : "",
          check && !inline ? "form-check-label" : "",
          check && inline ? "form-check-inline" : "",
          check && inline && disabled ? "disabled" : "",
          switch (size) {
          | None => ""
          | Some(s) => "col-form-label-" ++ Size.toString(s)
          },
          containsColClasses ? "col-form-label" : "",
          !check && !containsColClasses ? "form-control-label" : "",
          ColorsRe.Text.unWrap(color),
        ]
        ->(Belt.List.concat(colClasses))
        |> String.concat(" ");
      ReactDOMRe.createElementVariadic(
        tag,
        ~props={
          "className": classes,
          "htmlFor": Js.Nullable.fromOption(for_),
        } |. ReactDOMRe.objToDOMProps,
        children,
      );
    },
  };
};
