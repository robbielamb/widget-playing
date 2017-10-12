include Utils;

include Colors;

module Size = {
  type t =
    | None
    | Large
    | Small;
  let toString size =>
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

let component = ReasonReact.statelessComponent "Input";

let make
    tag::(tag: string)="p"
    id::(id: option string)=?
    name::(name: string)=""
    _type::(_type: inputType)=Text
    size::(size: Size.t)=Size.None
    plainText::(plainText: bool)=false
    placeholder::(placeholder: option string)=?
    disabled::(disabled: bool)=false
    multiple::(multiple: option bool)=?
    className::(className: option string)=?
    onInput::(onInput: option (ReactEventRe.Keyboard.t => unit))=?
    onChange::(onChange: option (ReactEventRe.Form.t => unit))=?
    value::(value: option string)=?
    children => {
  ...component,
  render: fun _self => {
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
      | _ => "input"
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
      [unwrapStr i className, Size.toString size, formControlClass] |> String.concat " ";
    let myProps: Js.t {..} = {
      "className": className,
      "id": Js.Null_undefined.from_opt id,
      "name": name,
      "type": typeAttribute,
      "placeholder": Js.Null_undefined.from_opt placeholder,
      "multiple": Js.Null_undefined.from_opt multiple,
      "disabled": Js.Boolean.to_js_boolean disabled,
      "onInput" : Js.Null_undefined.from_opt onInput,
      "onChange": Js.Null_undefined.from_opt onChange,
      "value": Js.Null_undefined.from_opt value
    };
    /* let myProps=      multiple ? {..myProps, "multiple": "multi"} : myProps; */
    ReasonReact.createDomElement tag props::myProps children
  }
};

module Label = {
  include LayoutRe.ColSizes;
  module Size = {
    type t =
      | SM
      | LG;
    let toString size =>
      switch size {
      | SM => "sm"
      | LG => "lg"
      };
  };
  let component = ReasonReact.statelessComponent "Form.Label";
  let make
      tag::(tag: string)="label"
      _for::(_for: option string)=?
      hidden::(hidden: bool)=false
      check::(check: bool)=false
      inline::(inline: bool)=false
      disabled::(disabled: bool)=false
      size::(size: option Size.t)=?
      color::(color: option TextColor.t)=?
      xs::(xs: option shape)=(Some (shape ()))
      sm::(sm: option shape)=?
      md::(md: option shape)=?
      lg::(lg: option shape)=?
      xl::(xl: option shape)=?
      className::(className: option string)=?
      children => {
    ...component,
    render: fun _self => {
      let colClasses = processShapeList xs sm md lg xl;
      let containsColClasses = List.length colClasses > 0;
      let classes =
        [
          unwrapStr i className,
          hidden ? "sr-only" : "",
          check && not inline ? "form-check-label" : "",
          check && inline ? "form-check-inline" : "",
          check && inline && disabled ? "disabled" : "",
          switch size {
          | None => ""
          | Some s => "col-form-label-" ^ Size.toString s
          },
          containsColClasses ? "col-form-label" : "",
          not check && not containsColClasses ? "form-control-label" : "",
          TextColor.unWrap color
        ] |>
        List.append colClasses |>
        String.concat " ";
      ReasonReact.createDomElement
        tag props::{"className": classes, "htmlFor": Js.Null_undefined.from_opt _for} children
    }
  };
};