include WidgetPlaying.Bootstrap;

let code: string =
  [%bs.raw {|require('Examples/FormsExample.re').default|}]
  |> Examples.prepCode;

let se = React.string;

[@react.component]
let make = () => {
  <Examples.Example title="Forms & Input">
    <Form>
      <Form.Group>
        <Input.Label htmlFor="exampleEmail"> {se("Email")} </Input.Label>
        <Input
          type_=Input.Email
          name="email"
          id="exampleEmail"
          placeholder="with a placeholder"
        />
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="examplePassword">
          {se("Password")}
        </Input.Label>
        <Input
          type_=Input.Password
          name="password"
          id="examplePassword"
          placeholder="password here"
        />
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="exampleRequired">
          {se("Required Field")}
        </Input.Label>
        <Input
          type_=Input.Text
          name="required"
          id="exampleRequired"
          placeholder="Required Text"
          required=true
        />
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="exampleDate"> {se("Date")} </Input.Label>
        <Input
          type_=Input.Date
          name="exampleDate"
          id="exampleDate"
          placeholder="Birthday!"
          required=true
        />
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="selectExample"> {se("Select")} </Input.Label>
        <Input.Select name="select" id="selectExample" placeholder="foo">
          <option> {se("1")} </option>
          <option> {se("2")} </option>
          <option> {se("3")} </option>
          <option> {se("4")} </option>
        </Input.Select>
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="selecMultitExample">
          {se("Select Multiple")}
        </Input.Label>
        <Input.Select
          name="multi-select"
          id="selectMultiExample"
          placeholder="foo"
          multiple=true>
          <option> {se("1")} </option>
          <option> {se("2")} </option>
          <option> {se("3")} </option>
          <option> {se("4")} </option>
          <option> {se("5")} </option>
          <option> {se("6")} </option>
        </Input.Select>
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="exampleTextArea">
          {se("Text Area")}
        </Input.Label>
        <Input
          type_=Input.TextArea
          name="textarea"
          id="exampleTextArea"
          placeholder="TextArea with a placeholder"
        />
      </Form.Group>
      <Form.Group>
        <Input.Label htmlFor="exampleFile">
          {se("File Upload Time")}
        </Input.Label>
        <Input
          type_=Input.File
          name="file"
          id="exampleFile"
          placeholder="with a placeholder"
        />
        <Form.Text>
          {se(
             "This is a bit of example text to help explain the dialog above.",
           )}
        </Form.Text>
      </Form.Group>
      <Form.Fieldset>
        <legend> {se("Hello Radio (buttons>")} </legend>
        <Form.Check>
          <Input.Label check=true>
            <Input type_=Input.Radio name="radio1" />
            {se(" Radio 1")}
          </Input.Label>
        </Form.Check>
        <Form.Check>
          <Input.Label check=true>
            <Input type_=Input.Radio name="radio1" />
            {se(" Radio 2")}
          </Input.Label>
        </Form.Check>
        <Form.Check disabled=true>
          <Input.Label check=true>
            <Input type_=Input.Radio name="radio1" disabled=true />
            {se(" Radio 3 - Disabled")}
          </Input.Label>
        </Form.Check>
      </Form.Fieldset>
      <Form.Check>
        <Input.Label check=true>
          <Input type_=Input.Checkbox name="check-box" />
          {se("  This is a checkbox")}
        </Input.Label>
      </Form.Check>
    </Form>
    {Examples.exampleHighlight(code)}
  </Examples.Example>;
};