include Utils;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString = (size) =>
    switch size {
    | None => ""
    | Large => "form-control-lg"
    | Small => "form-control-sm"
    };
};

type inputType =
  | Text
  | TextArea
  | Email
  | Password
  | File
  | Select
  | Radio
  | Checkbox
  | Url;

let component = ReasonReact.statelessComponent("Input");

let make =
    (
      ~tag: string="input",
      ~id: option(string)=?,
      ~name: string="",
      ~_type: inputType=Text,
      ~size: Size.t=Size.None,
      ~plainText: bool=false,
      ~placeholder: option(string)=?,
      ~disabled: bool=false,
      ~multiple: option(bool)=?,
      ~className: option(string)=?,
      ~onInput: option((ReactEventRe.Keyboard.t => unit))=?,
      ~onChange: option((ReactEventRe.Form.t => unit))=?,
      ~checked: option(bool)=?,
      ~value: option(string)=?,
      children
    ) => {
  ...component,
  render: (_self) => {
    let checkInput =
      switch _type {
      | Radio => true
      | Checkbox => true
      | _ => false
      };
    let fileInput = _type === File;
    let tag =
      switch _type {
      | TextArea => "textarea"
      | Select => "select"
      | _ => tag
      };
    let typeAttribute =
      switch _type {
      | Select => ""
      | TextArea => ""
      | Text => "text"
      | Password => "password"
      | File => "file"
      | Radio => "radio"
      | Checkbox => "checkbox"
      | Email => "email"
      | Url => "url"
      };
    let formControlClass =
      switch (plainText, fileInput, checkInput) {
      | (true, false, false) => "form-control-planetext"
      | (false, true, false) => "form-control-file"
      | (false, false, true) => "form-check-input"
      | (_, _, _) => "form-control"
      };
    let className =
      [unwrapStr(i, className), Size.toString(size), formControlClass] |> String.concat(" ");
    let myProps: Js.t({..}) = {
      "className": className,
      "id": Js.Null_undefined.from_opt(id),
      "name": name,
      "type": typeAttribute,
      "placeholder": Js.Null_undefined.from_opt(placeholder),
      "multiple": Js.Null_undefined.from_opt(multiple),
      "disabled": Js.Boolean.to_js_boolean(disabled),
      "onInput": Js.Null_undefined.from_opt(onInput),
      "onChange": Js.Null_undefined.from_opt(onChange),
      "checked": Js.Null_undefined.from_opt(checked),
      "value": Js.Null_undefined.from_opt(value)
    };
    /* let myProps=      multiple ? {..myProps, "multiple": "multi"} : myProps; */
    ReasonReact.createDomElement(tag, ~props=myProps, children)
  }
};

module Label = {
  include LayoutRe.ColSizes;
  module Size = {
    type t =
      | SM
      | LG;
    let toString = (size) =>
      switch size {
      | SM => "sm"
      | LG => "lg"
      };
  };
  let component = ReasonReact.statelessComponent("Form.Label");
  let make =
      (
        ~tag: string="label",
        ~_for: option(string)=?,
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
        children
      ) => {
    ...component,
    render: (_self) => {
      let colClasses = processShapeList(xs, sm, md, lg, xl);
      let containsColClasses = List.length(colClasses) > 0;
      let classes =
        [
          unwrapStr(i, className),
          hidden ? "sr-only" : "",
          check && ! inline ? "form-check-label" : "",
          check && inline ? "form-check-inline" : "",
          check && inline && disabled ? "disabled" : "",
          switch size {
          | None => ""
          | Some(s) => "col-form-label-" ++ Size.toString(s)
          },
          containsColClasses ? "col-form-label" : "",
          ! check && ! containsColClasses ? "form-control-label" : "",
          ColorsRe.Text.unWrap(color)
        ]
        |> List.append(colClasses)
        |> String.concat(" ");
      ReasonReact.createDomElement(
        tag,
        ~props={"className": classes, "htmlFor": Js.Null_undefined.from_opt(_for)},
        children
      )
    }
  };
};